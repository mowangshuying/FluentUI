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
    FluStyleSheetUitls::setQssByFileName("FluVSplitLine.qss", this, FluThemeUtils::getUtils()->getTheme());
}
