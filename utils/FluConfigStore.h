#pragma once

// Location layer for FluentUI configuration storage (header-only, QtCore only).
//
// Why this is split out: FluConfigUtils used to hard-code "../config/config.ini"
// in its constructor, so the anchor followed the process CWD. Whenever the working
// directory differs from the executable directory (launched from a shortcut, started
// from elsewhere, or shipped without the config/ folder), the theme and language
// silently fall back to their defaults and nothing is reported. This layer collects
// the three location segments (directory / file name / format), the path resolution
// and the JSON backend into stateless computation, leaving FluConfigUtils as the
// singleton facade that only reads and writes keys.
//
// The class holds no state: every member is static. It is never instantiated, so the
// constructor is explicitly deleted.

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMap>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>

// Configuration file format. The mapping onto QSettings::Format is done by
// FluConfigStore::settingsFormat().
enum class FluConfigFormat
{
    Ini,  // QSettings::IniFormat - the historical behaviour
    Json, // custom format: QSettings::registerFormat("json", ...), stored as a nested JSON object
};

class FluConfigStore
{
  public:
    // Pure static utility class, no instance state.
    FluConfigStore() = delete;

    // ---- Default anchors: kept identical to the pre-refactor hard-coded values, so
    // ---- behaviour is unchanged as long as no location is injected.

    static QString defaultDirPath()
    {
        return QStringLiteral("../config");
    }

    static QString defaultFileName()
    {
        return QStringLiteral("config");
    }

    static FluConfigFormat defaultFormat()
    {
        return FluConfigFormat::Ini;
    }

    static QString suffixFor(FluConfigFormat format)
    {
        return format == FluConfigFormat::Json ? QStringLiteral(".json") : QStringLiteral(".ini");
    }

    // Format name -> enum. The format field in a configuration file is hand-written
    // text, and case folding plus trimming should not be repeated at every call site
    // (three call sites, three folding rules = three results for one configuration),
    // so the folding lives here. Anything unrecognised falls back to the given default
    // (Ini): a mistyped format name should mean "use the old format", not "read no
    // configuration at all".
    static FluConfigFormat formatFromName(const QString& name, FluConfigFormat fallback = defaultFormat())
    {
        const QString trimmed = name.trimmed();
        if (trimmed.compare(QStringLiteral("json"), Qt::CaseInsensitive) == 0)
            return FluConfigFormat::Json;
        if (trimmed.compare(QStringLiteral("ini"), Qt::CaseInsensitive) == 0)
            return FluConfigFormat::Ini;
        return fallback;
    }

    // Inverse direction, for the write side and for diagnostics: print the current
    // format as the lower-case name that formatFromName() reads back (round-trip safe).
    static QString nameForFormat(FluConfigFormat format)
    {
        return format == FluConfigFormat::Json ? QStringLiteral("json") : QStringLiteral("ini");
    }

    // Anchoring a relative directory: when a configuration says "config" or
    // "../config", the result should be pinned to the anchor supplied by the caller
    // (typically QCoreApplication::applicationDirPath()) instead of drifting with the
    // process CWD - that drift is exactly what used to lose the theme. Absolute paths
    // are passed through unchanged (the caller already fixed the location), and so is
    // an empty anchor (when there is nothing to anchor to, do not guess).
    //
    // Folding is done with an explicit cleanPath rather than through absoluteFilePath:
    // measured on Qt 6.9, QDir("D:/app/bin").absoluteFilePath("../config") returns
    // "D:/app/bin/../config" - it only prepends the base, it does not fold ".."
    // (filePath() behaves the same). QSettings tolerates the unfolded form, but
    // diagnostic output would carry ".." and invite a wrong conclusion about where the
    // file went, and mkpath/exists comparisons would treat two spellings of one
    // directory as two directories.
    static QString anchorRelativeDir(const QString& dirPath, const QString& anchor)
    {
        const QString dir = dirPath.trimmed();
        if (dir.isEmpty() || anchor.isEmpty() || QDir::isAbsolutePath(dir))
            return dir;
        return QDir::cleanPath(QDir(anchor).absoluteFilePath(dir));
    }

    // ---- Path resolution ---------------------------------------------------------
    //
    // The final file path is assembled from three segments (directory / file name /
    // format). Rules:
    //   - empty dirPath  -> fall back to the default directory (relative paths resolve
    //     against the process CWD, absolute paths are used as they are)
    //   - empty fileName -> fall back to "config"
    //   - the extension always follows the format: passing "config.ini" with format
    //     Json yields "config.json". Rewriting the extension the caller supplied is
    //     preferable to letting QSettings parse a .ini file as JSON - a split between
    //     the format and the file on disk must never happen.

    static QString resolveFilePath(const QString& dirPath, const QString& fileName, FluConfigFormat format)
    {
        QString dir = dirPath.trimmed();
        if (dir.isEmpty())
            dir = defaultDirPath();

        QString name = fileName.trimmed();
        if (name.isEmpty())
            name = defaultFileName();

        const QString suffix = suffixFor(format);
        if (!name.endsWith(suffix, Qt::CaseInsensitive))
        {
            const int dot = name.lastIndexOf(QLatin1Char('.'));
            // dot > 0 rather than >= 0: a dot-only name such as ".json" is the whole
            // file name and must not be treated as if it were an extension.
            if (dot > 0)
                name = name.left(dot);
            name += suffix;
        }

        return QDir(dir).filePath(name);
    }

    // ---- Conversion between JSON and the flat QSettings keys ---------------------
    //
    // Internally QSettings is a flat QVariantMap layered by '/' (beginGroup("config")
    // plus setValue("theme") is the key "config/theme"). The JSON side stores the same
    // shape as a nested object, which reads like the [config] section of an ini file.

    // Nested object -> flat keys: {"config":{"theme":"Dark"}} -> "config/theme" = "Dark"
    static void flatten(const QJsonObject& obj, const QString& prefix, QVariantMap& out)
    {
        for (auto it = obj.constBegin(); it != obj.constEnd(); ++it)
        {
            const QString key = prefix.isEmpty() ? it.key() : prefix + QLatin1Char('/') + it.key();
            const QJsonValue value = it.value();
            if (value.isObject())
                flatten(value.toObject(), key, out);
            else
                out.insert(key, value.toVariant());
        }
    }

    // Flat keys -> nested object (recursion entry point for buildObject)
    static QJsonObject buildObject(const QVariantMap& flat)
    {
        QJsonObject obj;
        // Keys containing '/' are grouped by their first segment and recursed with that
        // segment stripped. Grouping rather than inserting segment by segment is needed
        // because QJsonObject cannot hand out a reference into a nested object: with
        // value semantics the tree can only be assembled bottom-up.
        QMap<QString, QVariantMap> groups;
        for (auto it = flat.constBegin(); it != flat.constEnd(); ++it)
        {
            const int slash = it.key().indexOf(QLatin1Char('/'));
            if (slash < 0)
            {
                obj.insert(it.key(), QJsonValue::fromVariant(it.value()));
                continue;
            }
            groups[it.key().left(slash)].insert(it.key().mid(slash + 1), it.value());
        }
        for (auto it = groups.constBegin(); it != groups.constEnd(); ++it)
            obj.insert(it.key(), buildObject(it.value()));
        return obj;
    }

    // ---- Read/write callbacks for the custom QSettings format --------------------
    //
    // The signatures must match QSettings::ReadFunc / WriteFunc
    // (bool(*)(QIODevice&, SettingsMap&)). Static member functions carry no `this`, so
    // taking their address yields a plain function pointer that registerFormat accepts.

    static bool readJson(QIODevice& device, QVariantMap& map)
    {
        const QByteArray raw = device.readAll();
        if (raw.trimmed().isEmpty())
            return true; // an empty file is an empty configuration, not an error: on a
                         // first run the file does not exist yet

        const QJsonDocument doc = QJsonDocument::fromJson(raw);
        if (!doc.isObject())
            return false; // let QSettings raise FormatError; the read side then falls
                          // back to the per-key defaults
        flatten(doc.object(), QString(), map);
        return true;
    }

    static bool writeJson(QIODevice& device, const QVariantMap& map)
    {
        const QByteArray raw = QJsonDocument(buildObject(map)).toJson(QJsonDocument::Indented);
        return device.write(raw) == raw.size();
    }

    // Register once, reuse everywhere: registerFormat is idempotent for the same
    // extension, but calling it repeatedly still consumes a fresh CustomFormat slot,
    // so a function-local static pins the first result (a local static in a static
    // member function is unique across translation units, so no definition file is
    // needed).
    static QSettings::Format jsonFormat()
    {
        static const QSettings::Format fmt =
            QSettings::registerFormat(QStringLiteral("json"), &readJson, &writeJson, Qt::CaseSensitive);
        return fmt;
    }

    static QSettings::Format settingsFormat(FluConfigFormat format)
    {
        return format == FluConfigFormat::Json ? jsonFormat() : QSettings::IniFormat;
    }

    // ---- Factory ------------------------------------------------------------------

    // Create the directory before handing a path to QSettings: QSettings does not
    // create parent directories, and when the directory is missing the write fails
    // silently - that is precisely how the theme was lost once config/ disappeared.
    static QString ensureDirFor(const QString& filePath)
    {
        const QString dir = QFileInfo(filePath).absolutePath();
        if (!dir.isEmpty() && !QDir().mkpath(dir))
            return QString();
        return filePath;
    }

    static QSettings* createSettings(const QString& dirPath, const QString& fileName, FluConfigFormat format,
                                     QObject* parent = nullptr)
    {
        const QString filePath = resolveFilePath(dirPath, fileName, format);
        return new QSettings(ensureDirFor(filePath), settingsFormat(format), parent);
    }
};
