#include "FluVSplitLine.h"

FluVSplitLine::FluVSplitLine(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setFixedHeight(1);
    // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVSplitLine.qss", this);
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
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVSplitLine.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluVSplitLine.qss", this);
    }
}
