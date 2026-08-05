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
    m_verticalScrollBar->installEventFilter(this);
    m_horizontalScrollBar->installEventFilter(this);
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
        QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);

        // 如果是自定义 scrollbar 本身收到滚轮，直接更新对应原生 scrollbar
        if (watched == m_verticalScrollBar || watched == m_horizontalScrollBar)
        {
            auto* scrollbar = (watched == m_verticalScrollBar) ? m_verticalScrollBar : m_horizontalScrollBar;
            auto* nativeBar = scrollbar->getOriginalScrollBar();
            int delta = (wheelEvent->angleDelta().y() != 0) ? -wheelEvent->angleDelta().y() : -wheelEvent->angleDelta().x();
            nativeBar->setValue(nativeBar->value() + delta);
            event->accept();
            return true;
        }

        // viewport 滚轮，直接更新原生 scrollbar
        if (watched == m_scrollArea->viewport())
        {
            if (wheelEvent->angleDelta().y() != 0)
            {
                auto* bar = m_scrollArea->verticalScrollBar();
                bar->setValue(bar->value() - wheelEvent->angleDelta().y());
            }
            else if (wheelEvent->angleDelta().x() != 0)
            {
                auto* bar = m_scrollArea->horizontalScrollBar();
                bar->setValue(bar->value() - wheelEvent->angleDelta().x());
            }
            event->accept();
            return true;
        }
    }

    return QObject::eventFilter(watched, event);
}
