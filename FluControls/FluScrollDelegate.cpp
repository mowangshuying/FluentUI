#include "FluScrollDelegate.h"
#include "FluScrollArea.h"
#include "FluScrollBar.h"

FluScrollDelegate::FluScrollDelegate(FluScrollArea* scrollArea /*= nullptr*/) : QObject(scrollArea)
{
    m_scrollArea = scrollArea;
    m_vScrollBar = new FluScrollBar(Qt::Vertical, scrollArea);
    m_hSrollBar = new FluScrollBar(Qt::Horizontal, scrollArea);
}
