#include "FluScrollArea.h"

FluScrollArea::FluScrollArea(QWidget* parent /*= nullptr*/) : QScrollArea(parent)
{
    m_scrollDelegate = new FluScrollDelegate(this);
}

void FluScrollArea::hideVScrollBar()
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollDelegate->getVScrollBar()->setHideScrollBar(true);
}

void FluScrollArea::hideHScrollBar()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollDelegate->getHScrollBar()->setHideScrollBar(true);
}
