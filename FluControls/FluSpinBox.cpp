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
    FluStyleSheetUitls::drawBottomLineIndicator(this, &painter);
}

void FluSpinBox::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluSpinBox.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluSpinBox.qss"), this);
    }
}
