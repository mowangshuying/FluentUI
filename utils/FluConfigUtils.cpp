#include "FluConfigUtils.h"

#include <QCoreApplication>
#include <QFileInfo>

FluConfigUtils* FluConfigUtils::m_configUtils = nullptr;
QString FluConfigUtils::m_configDirPath;      // empty -> FluConfigStore::defaultDirPath()
QString FluConfigUtils::m_configFileName;     // empty -> FluConfigStore::defaultFileName()
FluConfigFormat FluConfigUtils::m_configFormat = FluConfigStore::defaultFormat();

FluConfigUtils::FluConfigUtils(QObject* parent) : QObject(parent)
{
    // Used to be new QSettings("../config/config.ini", QSettings::IniFormat): both the
    // path and the format were hard-coded. They are now resolved from the three
    // location segments, whose defaults are exactly that hard-coded pair, so the
    // behaviour is unchanged for anyone who never calls configure().
    rebuildSettings();
}

FluConfigUtils::~FluConfigUtils()
{
    delete m_settings;
    m_settings = nullptr;
}

void FluConfigUtils::configure(const QString& dirPath, const QString& fileName, FluConfigFormat format)
{
    // Repeating the same injection must not rebuild: rebuilding deletes the QSettings
    // that callers may still be referencing, since getSettings() hands out a raw
    // pointer.
    if (m_configDirPath == dirPath && m_configFileName == fileName && m_configFormat == format)
        return;

    m_configDirPath = dirPath;
    m_configFileName = fileName;
    m_configFormat = format;

    if (m_configUtils != nullptr)
        m_configUtils->rebuildSettings();
}

QString FluConfigUtils::configDirPath()
{
    const QString dir = m_configDirPath.trimmed();
    return dir.isEmpty() ? FluConfigStore::defaultDirPath() : dir;
}

QString FluConfigUtils::configFileName()
{
    const QString name = m_configFileName.trimmed();
    return name.isEmpty() ? FluConfigStore::defaultFileName() : name;
}

FluConfigFormat FluConfigUtils::configFormat()
{
    return m_configFormat;
}

QString FluConfigUtils::configFilePath()
{
    return FluConfigStore::resolveFilePath(m_configDirPath, m_configFileName, m_configFormat);
}

void FluConfigUtils::rebuildSettings()
{
    if (m_settings != nullptr)
    {
        // Sync before switching location so in-memory values reach the old file instead
        // of disappearing together with the object.
        m_settings->sync();
        delete m_settings;
        m_settings = nullptr;
    }
    m_settings = FluConfigStore::createSettings(m_configDirPath, m_configFileName, m_configFormat);
}

FluTheme FluConfigUtils::getTheme()
{
    m_settings->sync();
    m_settings->beginGroup("config");
    QString themeName = m_settings->value("theme").toString();
    m_settings->endGroup();
    if (themeName == "Light")
    {
        return FluTheme::Light;
    }
    else if (themeName == "Dark")
    {
        return FluTheme::Dark;
    }
    return FluTheme::Light;
}

void FluConfigUtils::setTheme(FluTheme theme)
{
    m_settings->beginGroup("config");
    if (theme == FluTheme::Light)
    {
        m_settings->setValue("theme", "Light");
    }
    else
    {
        m_settings->setValue("theme", "Dark");
    }
    m_settings->endGroup();
    m_settings->sync();
}

QString FluConfigUtils::getLanguage()
{
    m_settings->sync();
    m_settings->beginGroup("config");
    QString language = m_settings->value("language", "zh-CN").toString();
    m_settings->endGroup();
    return language;
}

QString FluConfigUtils::getTranslationLanguage()
{
    m_settings->sync();
    m_settings->beginGroup("translation");
    QString language = m_settings->value("language", "zh-CN").toString();
    m_settings->endGroup();
    return language;
}

void FluConfigUtils::setLanguage(QString lang)
{
    m_settings->beginGroup("config");
    m_settings->setValue("language", lang);
    m_settings->endGroup();
    m_settings->sync();
}

int FluConfigUtils::getNavWidth()
{
    m_settings->sync();
    m_settings->beginGroup("config");
    int navWidth = m_settings->value("navWidth", 300).toInt();
    m_settings->endGroup();
    return navWidth;
}

void FluConfigUtils::setNavWidth(int width)
{
    m_settings->beginGroup("config");
    m_settings->setValue("navWidth", width);
    m_settings->endGroup();
    m_settings->sync();
}

bool FluConfigUtils::getViewCollapsed()
{
    m_settings->sync();
    m_settings->beginGroup("config");
    bool isCollapsed = m_settings->value("viewCollapsed", false).toBool();
    m_settings->endGroup();
    return isCollapsed;
}

void FluConfigUtils::setViewCollapsed(bool isCollapsed)
{
    m_settings->beginGroup("config");
    m_settings->setValue("viewCollapsed", isCollapsed);
    m_settings->endGroup();
    m_settings->sync();
}

int FluConfigUtils::getNavStyle()
{
    m_settings->sync();
    m_settings->beginGroup("config");
    int style = m_settings->value("navStyle", 0).toInt();
    m_settings->endGroup();
    return style;
}

void FluConfigUtils::setNavStyle(int style)
{
    m_settings->beginGroup("config");
    m_settings->setValue("navStyle", style);
    m_settings->endGroup();
    m_settings->sync();
}

void FluConfigUtils::exportToIni(const QString& filePath)
{
    QSettings exportSettings(filePath, QSettings::IniFormat);
    // Walk every key of the current backend and export it
    QStringList allKeys = m_settings->allKeys();
    for (const QString& key : allKeys)
    {
        exportSettings.setValue(key, m_settings->value(key));
    }
    m_settings->sync();
}

QSettings* FluConfigUtils::getSettings()
{
    return m_settings;
}
