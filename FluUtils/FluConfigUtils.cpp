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
    m_settings->beginGroup("config");
    QString languageStr = m_settings->value("language", "en-US").toString();
    m_settings->endGroup();

    return languageStr;
}

void FluConfigUtils::setLanguage(QString language)
{
    m_settings->beginGroup("config");
    m_settings->setValue("language", language);
    m_settings->endGroup();
}
