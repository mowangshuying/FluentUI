#include "FluHSplitLine.h"

FluHSplitLine::FluHSplitLine(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setFixedWidth(1);
    onThemeChanged();
}

void FluHSplitLine::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluHSplitLine::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluHSplitLine.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluHSplitLine.qss"), this);
    }
}
