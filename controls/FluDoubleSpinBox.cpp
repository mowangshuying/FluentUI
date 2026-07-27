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
    FluStyleSheetUtils::drawBottomLineIndicator(this, &painter);
}

void FluDoubleSpinBox::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluDoubleSpinBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
