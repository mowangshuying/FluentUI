#include "FluThemeUtils.h"

FluThemeUtils* FluThemeUtils::m_themeUtils = nullptr;
FluThemeUtils::FluThemeUtils(QObject* object /*= nullptr*/) : QObject(object)
{
    m_theme = FluTheme::Light;
}
