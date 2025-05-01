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
    FluStyleSheetUitls::setQssByFileName("FluHSplitLine.qss", this, FluThemeUtils::getUtils()->getTheme());
}
