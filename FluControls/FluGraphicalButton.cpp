#include "FluGraphicalButton.h"

FluGraphicalButton::FluGraphicalButton(QWidget* parent /*= nullptr*/) : QPushButton(parent)
{
    setFixedSize(50, 50);
    setIconSize(QSize(28, 28));

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluGraphicalButton::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluGraphicalButton.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluGraphicalButton.qss"), this);
    }
}
