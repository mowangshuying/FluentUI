#include "FluSlider.h"

FluSlider::FluSlider(QWidget* parent /*= nullptr*/) : QSlider(parent)
{
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSlider.qss", this);
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluSlider::FluSlider(Qt::Orientation orientation, QWidget* parent /*= nullptr*/) : QSlider(orientation, parent)
{
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSlider.qss", this);
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluSlider::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSlider.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluSlider.qss", this);
    }
}
