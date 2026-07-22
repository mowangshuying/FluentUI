#include "FluDatePickerViewMask.h"
#include <QEnterEvent>
#include "../Utils/FluUtils.h"

FluDatePickerViewMaskItem::FluDatePickerViewMaskItem(QString text, int width, int height)
{
    m_text = text;
    m_width = width;
    m_height = height;
}

FluDatePickerViewMask::FluDatePickerViewMask(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_currentIndex = -1;
    setMouseTracking(true);
}

void FluDatePickerViewMask::addItem(QString text, int width, int height)
{
    FluDatePickerViewMaskItem item(text, width, height);
    m_items.push_back(item);
}

void FluDatePickerViewMask::setItemText(int index, QString text)
{
    m_items[index].m_text = text;
}

void FluDatePickerViewMask::paintBackground(QPainter& painter)
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(getBackgroundColorEx());
    painter.drawRoundedRect(rect().adjusted(4, 0, -4, 0), 4, 4);
}

void FluDatePickerViewMask::paintText(QPainter& painter)
{
    painter.setPen(getTextColorEx());

    int currentX = 0;
    int currentY = 0;
    for (auto item : m_items)
    {
        painter.drawText(QRect(currentX, currentY, item.m_width, item.m_height), Qt::AlignCenter, item.m_text);
        currentX += item.m_width;
    }
}

// void FluDatePickerViewMask::enterEvent(QEnterEvent* event)
//{
//     int x = mapFromGlobal(QCursor().pos()).x();
//     for (int i = 0; i < m_items.size(); i++)
//     {
//         if (x >= m_items[i].m_nWidth)
//             x -= m_items[i].m_nWidth;
//         else
//         {
//             emit enterChanged(i, event);
//             break;
//         }
//     }
// }
//
// void FluDatePickerViewMask::leaveEvent(QEvent* event)
//{
//     int x = mapFromGlobal(QCursor().pos()).x();
//     for (int i = 0; i < m_items.size(); i++)
//     {
//         if (x >= m_items[i].m_nWidth)
//             x -= m_items[i].m_nWidth;
//         else
//         {
//             emit leaveChanged(i, event);
//             break;
//         }
//     }
// }

void FluDatePickerViewMask::mouseMoveEvent(QMouseEvent* event)
{
    // LOG_DEBUG << "called";
    int x = mapFromGlobal(QCursor().pos()).x();

    int temporaryIndex = -1;
    for (int i = 0; i < m_items.size(); i++)
    {
        if (x >= m_items[i].m_width)
        {
            x -= m_items[i].m_width;
        }
        else
        {
            temporaryIndex = i;
            break;
        }
    }

    if (m_currentIndex == -1 || m_currentIndex == temporaryIndex)
    {
        m_currentIndex = temporaryIndex;

        QPointF localPoint;
        QPointF scenePoint;
        QPointF globalPoint;
        QEnterEvent hoverEnterEvent(localPoint, scenePoint, globalPoint);
        emit enterChanged(m_currentIndex, &hoverEnterEvent);
        return;
    }

    if (m_currentIndex != temporaryIndex)
    {
        QEvent hoverLeaveEvent(QEvent::Leave);
        emit leaveChanged(m_currentIndex, &hoverLeaveEvent);

        QPointF localPoint;
        QPointF scenePoint;
        QPointF globalPoint;
        QEnterEvent hoverEnterEvent(localPoint, scenePoint, globalPoint);
        emit enterChanged(temporaryIndex, &hoverEnterEvent);

        m_currentIndex = temporaryIndex;
    }
}

void FluDatePickerViewMask::wheelEvent(QWheelEvent* event)
{
    int x = mapFromGlobal(QCursor().pos()).x();
    for (int i = 0; i < m_items.size(); i++)
    {
        if (x >= m_items[i].m_width)
        {
            x -= m_items[i].m_width;
        }
        else
        {
            emit wheelChanged(i, event);
            break;
        }
    }
}

void FluDatePickerViewMask::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(Qt::NoPen);

    paintBackground(painter);

    paintText(painter);
}
