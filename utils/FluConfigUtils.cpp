#include "FluConfigUtils.h"

FluConfigUtils* FluConfigUtils::m_configUtils = nullptr;
FluConfigUtils::FluConfigUtils(QObject* parent /*= nullptr*/) : QObject(parent)
{
    m_settings = new QSettings("../config/config.ini", QSettings::IniFormat);
}

FluConfigUtils::~FluConfigUtils()
{
    delete m_settings;
}

FluTheme FluConfigUtils::getTheme()
{
    FluTheme theme = FluTheme::Light;
    m_settings->sync();
    m_settings->beginGroup("config");
    QString themeStr = m_settings->value("theme", "Light").toString();
    m_settings->endGroup();

    if (themeStr == "Light")
        theme = FluTheme::Light;
    else if (themeStr == "Dark")
        theme = FluTheme::Dark;
    else if (themeStr == "AtomOneDark")
        theme = FluTheme::AtomOneDark;
    return theme;
}

void FluConfigUtils::setTheme(FluTheme theme)
{
    // config/theme
    m_settings->sync();
    m_settings->beginGroup("config");

    if (theme == FluTheme::Light)
    {
        m_settings->setValue("theme", "Light");
    }
    else if (theme == FluTheme::Dark)
    {
        m_settings->setValue("theme", "Dark");
    }
    else if (theme == FluTheme::AtomOneDark)
    {
        m_settings->setValue("theme", "AtomOneDark");
    }

    m_settings->endGroup();
}

QString FluConfigUtils::getLanguage()
{
    m_settings->sync();
    m_settings->beginGroup("config");
    QString languageStr = m_settings->value("language", "en-US").toString();
    m_settings->endGroup();

    return languageStr;
}

void FluConfigUtils::setLanguage(QString language)
{
    m_settings->sync();
    m_settings->beginGroup("config");
    m_settings->setValue("language", language);
    m_settings->endGroup();
}

int FluConfigUtils::getNavWidth()
{
    m_settings->sync();
    m_settings->beginGroup("config");
    int width = m_settings->value("navWidth", 300).toInt();
    m_settings->endGroup();
    return width;
}

void FluConfigUtils::setNavWidth(int width)
{
    m_settings->sync();
    m_settings->beginGroup("config");
    m_settings->setValue("navWidth", width);
    m_settings->endGroup();
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
    m_settings->sync();
    m_settings->beginGroup("config");
    m_settings->setValue("navStyle", style);
    m_settings->endGroup();
}

bool FluConfigUtils::getViewCollapsed()
{
    m_settings->sync();
    m_settings->beginGroup("config");
    bool collapsed = m_settings->value("viewCollapsed", false).toBool();
    m_settings->endGroup();
    return collapsed;
}

void FluConfigUtils::setViewCollapsed(bool collapsed)
{
    m_settings->sync();
    m_settings->beginGroup("config");
    m_settings->setValue("viewCollapsed", collapsed);
    m_settings->endGroup();
}

QSettings* FluConfigUtils::getSettings()
{
    m_settings->sync();
    return m_settings;
}
