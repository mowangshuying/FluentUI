#include "FluSpinBox.h"

FluSpinBox::FluSpinBox(QWidget* parent /*= nullptr*/) : QSpinBox(parent)
{
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluSpinBox::paintEvent(QPaintEvent* event)
{
    QSpinBox::paintEvent(event);
    if (!hasFocus())
        return;

    QPainter painter(this);
    FluStyleSheetUtils::drawBottomLineIndicator(this, &painter);
}

void FluSpinBox::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluSpinBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
