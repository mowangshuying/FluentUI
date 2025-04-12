#include "FluStyleButton.h"

FluStyleButton::FluStyleButton(QWidget* parent /*= nullptr*/) : QPushButton(parent)
{
    setFixedSize(200, 30);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluStyleButton::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluStyleButton.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluStyleButton.qss"), this);
    }
}
