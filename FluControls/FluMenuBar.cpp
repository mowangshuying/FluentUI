#include "FluMenuBar.h"

FluMenuBar::FluMenuBar(QWidget* parent /*= nullptr*/) : QMenuBar(parent)
{
    setMouseTracking(true);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluMenuBar::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluMenuBar.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluMenuBar.qss"), this);
    }
}
