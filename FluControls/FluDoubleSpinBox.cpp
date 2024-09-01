#include "FluDoubleSpinBox.h"

FluDoubleSpinBox::FluDoubleSpinBox(QWidget* parent /*= nullptr*/) : QDoubleSpinBox(parent)
{
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluDoubleSpinBox::paintEvent(QPaintEvent* event)
{
    QDoubleSpinBox::paintEvent(event);
    if (!hasFocus())
        return;

    QPainter painter(this);
    FluStyleSheetUitls::drawBottomLineIndicator(this, &painter);
}

void FluDoubleSpinBox::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDoubleSpinBox.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluDoubleSpinBox.qss", this);
    }
}
