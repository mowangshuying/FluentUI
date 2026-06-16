#include "FluSlider.h"

FluSlider::FluSlider(QWidget* parent /*= nullptr*/) : QSlider(parent)
{
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluSlider::FluSlider(Qt::Orientation orientation, QWidget* parent /*= nullptr*/) : QSlider(orientation, parent)
{
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluSlider::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluSlider.qss", this, FluThemeUtils::getUtils()->getTheme());
}
