#include "FluStyleButton.h"

FluStyleButton::FluStyleButton(QWidget* parent /*= nullptr*/) : QPushButton(parent)
{
    setFixedSize(200, 30);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
}

void FluStyleButton::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluStyleButton.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluStyleButton.qss", this);
    }
}
