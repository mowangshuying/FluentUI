#include "FluDatePickerViewMask.h"
#include <QEnterEvent>
#include "../FluUtils/FluUtils.h"

FluDatePickerViewMaskItem::FluDatePickerViewMaskItem(QString text, int width, int height)
{
    m_text = text;
    m_nWidth = width;
    m_nHeight = height;
}

FluDatePickerViewMask::FluDatePickerViewMask(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_nCurIndex = -1;
    setMouseTracking(true);
}

void FluDatePickerViewMask::addItem(QString text, int nW, int nH)
{
    FluDatePickerViewMaskItem item(text, nW, nH);
    m_items.push_back(item);
}

void FluDatePickerViewMask::setItemText(int nIndex, QString text)
{
    m_items[nIndex].m_text = text;
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

    int nX = 0;
    int nY = 0;
    for (auto item : m_items)
    {
        painter.drawText(QRect(nX, nY, item.m_nWidth, item.m_nHeight), Qt::AlignCenter, item.m_text);
        nX += item.m_nWidth;
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
    // LOG_DEBUG << "x:" << x;

    int nTmpIndex = -1;
    for (int i = 0; i < m_items.size(); i++)
    {
        if (x >= m_items[i].m_nWidth)
        {
            x -= m_items[i].m_nWidth;

            // QPointF localP;
            // QPointF senceP;
            // QPointF globalP;
            // QEnterEvent tmpEvent(localP, senceP, globalP);
            // emit enterChanged(i, &tmpEvent);
        }
        else
        {
            // QEvent tmpEvent(QEvent::None);
            //  emit leaveChanged(i, &tmpEvent);
            // break;

            ///* QPointF localP;
            // QPointF senceP;
            // QPointF globalP;
            // QEnterEvent tmpEvent(localP, senceP, globalP);*/
            // emit enterChanged(i, &tmpEvent);
            nTmpIndex = i;
            break;
        }
    }

    if (m_nCurIndex == -1 || m_nCurIndex == nTmpIndex)
    {
        m_nCurIndex = nTmpIndex;

        QPointF localP;
        QPointF senceP;
        QPointF globalP;
        QEnterEvent tmpEvent(localP, senceP, globalP);
        emit enterChanged(m_nCurIndex, &tmpEvent);
        return;
    }

    if (m_nCurIndex != nTmpIndex)
    {
        QEvent tmpLeaveEvent(QEvent::Leave);
        emit leaveChanged(m_nCurIndex, &tmpLeaveEvent);

        QPointF localP;
        QPointF senceP;
        QPointF globalP;
        QEnterEvent tmpEnterEvent(localP, senceP, globalP);
        emit enterChanged(nTmpIndex, &tmpEnterEvent);

        m_nCurIndex = nTmpIndex;
    }
}

void FluDatePickerViewMask::wheelEvent(QWheelEvent* event)
{
    int x = mapFromGlobal(QCursor().pos()).x();
    for (int i = 0; i < m_items.size(); i++)
    {
        if (x >= m_items[i].m_nWidth)
        {
            x -= m_items[i].m_nWidth;
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
