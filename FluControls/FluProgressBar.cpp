#include "FluProgressBar.h"

FluProgressBar::FluProgressBar(QWidget* parent /*= nullptr*/) : QProgressBar(parent)
{
    setTextVisible(false);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluProgressBar::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluProgressBar.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluProgressBar.qss"), this);
    }
}
