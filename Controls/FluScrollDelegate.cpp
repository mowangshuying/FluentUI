#include "FluScrollDelegate.h"
// #include "FluScrollArea.h"
#include "FluScrollBar.h"
#include <QAbstractScrollArea>
#include <QAbstractItemView>

FluScrollDelegate::FluScrollDelegate(QAbstractScrollArea* scrollArea /*= nullptr*/) : QObject(scrollArea)
{
    m_scrollArea = scrollArea;
    m_verticalScrollBar = new FluScrollBar(Qt::Vertical, scrollArea);
    m_horizontalScrollBar = new FluScrollBar(Qt::Horizontal, scrollArea);

    auto itemView = qobject_cast<QAbstractItemView*>(scrollArea);
    if (itemView != nullptr)
    {
        itemView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        itemView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    }

    m_scrollArea->viewport()->installEventFilter(this);
}

FluScrollBar* FluScrollDelegate::getVerticalScrollBar()
{
    return m_verticalScrollBar;
}

FluScrollBar* FluScrollDelegate::getHorizontalScrollBar()
{
    return m_horizontalScrollBar;
}

bool FluScrollDelegate::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::Wheel)
    {
        QWheelEvent* wheelEvent = (QWheelEvent*)(event);
        if (wheelEvent->angleDelta().y() != 0)
        {
            m_verticalScrollBar->scrollCurrentValue(-wheelEvent->angleDelta().y());
        }
        else
        {
            m_horizontalScrollBar->scrollCurrentValue(-wheelEvent->angleDelta().x());
        }
        event->setAccepted(true);
        return true;
    }

    return QObject::eventFilter(watched, event);
}
