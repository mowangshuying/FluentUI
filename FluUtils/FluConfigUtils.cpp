#include "FluConfigUtils.h"

FluConfigUtils::FluConfigUtils(QObject* parent /*= nullptr*/) : QObject(parent)
{
    m_settings = new QSettings("../config/config.ini");
}

FluConfigUtils::~FluConfigUtils()
{
    delete m_settings;
}

FluTheme FluConfigUtils::getTheme()
{
    FluTheme theme;
    m_settings->beginGroup("config");
    QString themeStr = m_settings->value("theme", "Light").toString();
    m_settings->endGroup();

    if (themeStr == "Light")
        theme = FluTheme::Light;
    else
        theme = FluTheme::Dark;
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
    else
    {
        m_settings->setValue("theme", "Dark");
    }

    m_settings->endGroup();
}
