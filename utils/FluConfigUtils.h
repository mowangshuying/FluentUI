#pragma once

#include <QObject>
#include <QSettings>
#include <QString>

#include "FluConfigStore.h"
#include "FluThemeUtils.h"

// FluentUI configuration facade (singleton). The configuration file is no longer
// hard-coded to ../config/config.ini: the directory, the file name and the format
// (Ini / Json) can all be injected by the caller through the static configure() entry
// point. The defaults are the pre-refactor hard-coded values (../config + config +
// Ini -> "../config/config.ini"), so behaviour stays byte-for-byte identical as long
// as configure() is never called. Path resolution and the JSON backend live in
// FluConfigStore.h (pure QtCore).
class FluConfigUtils : public QObject
{
  protected:
    FluConfigUtils(QObject* parent = nullptr);
    ~FluConfigUtils();

  public:
    static FluConfigUtils* getUtils()
    {
        if (m_configUtils == nullptr)
            m_configUtils = new FluConfigUtils();
        return m_configUtils;
    }

    // ---- configuration location injection ----
    // All three segments are supplied at once: directory (empty -> "../config"), file
    // name (empty -> "config", may carry an extension, the effective extension is
    // forced by the format) and format (Ini -> .ini / Json -> .json).
    // The right moment is before the first getUtils() call, i.e. right after the
    // caller has constructed its QApplication. If the singleton already exists, the
    // backend is rebuilt in place: the old values are synced to disk first but are
    // NOT migrated to the new path, because changing the location means changing the
    // file and the old data stays where it was. Rebuilding invalidates every raw
    // pointer previously handed out by getSettings().
    static void configure(const QString& dirPath, const QString& fileName, FluConfigFormat format);

    // The three location segments currently in effect (empty values have already fallen
    // back to their defaults, so what is returned is the set actually in use).
    static QString configDirPath();
    static QString configFileName();
    static FluConfigFormat configFormat();
    // The full file path resolved from the three segments (for diagnostics and logging).
    static QString configFilePath();

    // public:
    FluTheme getTheme();
    void setTheme(FluTheme theme);

    QString getLanguage();
    void setLanguage(QString lang);

    QString getTranslationLanguage();

    int getNavWidth();
    void setNavWidth(int width);

    bool getViewCollapsed();
    void setViewCollapsed(bool isCollapsed);

    int getNavStyle();
    void setNavStyle(int style);

    void exportToIni(const QString& filePath);

    QSettings* getSettings();

  protected:
    // Rebuild m_settings from the current three-segment location (shared by configure()
    // and by the constructor).
    void rebuildSettings();

    static FluConfigUtils* m_configUtils;
    // The injected location is kept in statics rather than in instance members,
    // otherwise configure() could not take effect before the singleton exists.
    static QString m_configDirPath;
    static QString m_configFileName;
    static FluConfigFormat m_configFormat;

    // Must be initialized in place to nullptr: the constructor runs rebuildSettings(),
    // whose first act is "if (m_settings != nullptr) sync + delete". The member is a
    // raw pointer and is not in the constructor's initializer list, so an uninitialized
    // read yields a garbage heap value and deleting a wild pointer is undefined
    // behaviour that crashes outright; a caller only survives by accidentally landing
    // on a zeroed page.
    QSettings* m_settings = nullptr;
};
