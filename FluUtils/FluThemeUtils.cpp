#include "FluThemeUtils.h"
#include "FluConfigUtils.h"

FluThemeUtils* FluThemeUtils::m_themeUtils = nullptr;
FluThemeUtils::FluThemeUtils(QObject* object /*= nullptr*/) : QObject(object)
{
    m_theme = FluTheme::Light;
#ifdef _DEBUG
    // m_theme = FluTheme::Custom;
#endif
    m_theme = FluConfigUtils::getUtils()->getTheme();
}

FluTheme FluThemeUtils::getTheme()
{
    return m_theme;
}

void FluThemeUtils::setTheme(FluTheme theme)
{
    m_theme = theme;
    FluConfigUtils::getUtils()->setTheme(theme);
    emit themeChanged(m_theme);
}

QString FluThemeUtils::getThemeName()
{
    switch (getUtils()->getTheme())
    {
        case FluTheme::Light:
            return "light";
        case FluTheme::Dark:
            return "dark";
        case FluTheme::AtomOneDark:
            return "atomOneDark";
        default:
            return "light";
    }
}

FluThemeUtils* FluThemeUtils::getUtils()
{
    if (m_themeUtils == nullptr)
        m_themeUtils = new FluThemeUtils();
    return m_themeUtils;
}
