#include "FluVSplitLine.h"

FluVSplitLine::FluVSplitLine(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setFixedHeight(1);
    onThemeChanged();
}

void FluVSplitLine::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluVSplitLine::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluVSplitLine.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluVSplitLine.qss"), this);
    }
}
