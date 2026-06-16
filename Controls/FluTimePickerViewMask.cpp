#include "FluTimePickerViewMask.h"

FluTimePickerViewMaskItem::FluTimePickerViewMaskItem(QString text, int width, int height)
{
    m_text = text;
    m_nWidth = width;
    m_nHeight = height;
}

FluTimePickerViewMask::FluTimePickerViewMask(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_nCurIndex = -1;
    setMouseTracking(true);
}

void FluTimePickerViewMask::addItem(QString text, int nW, int nH)
{
    FluTimePickerViewMaskItem item(text, nW, nH);
    m_items.push_back(item);
}

void FluTimePickerViewMask::setItemText(int nIndex, QString text)
{
    m_items[nIndex].m_text = text;
}

void FluTimePickerViewMask::paintBackground(QPainter& painter)
{
    QColor backgroundColor;
    painter.setPen(Qt::NoPen);
    painter.setBrush(getBackgroundColorEx());
    painter.drawRoundedRect(rect().adjusted(4, 0, -4, 0), 4, 4);
}

void FluTimePickerViewMask::paintText(QPainter& painter)
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

void FluTimePickerViewMask::mouseMoveEvent(QMouseEvent* event)
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

void FluTimePickerViewMask::wheelEvent(QWheelEvent* event)
{
    int x = mapFromGlobal(QCursor().pos()).x();
    for (int i = 0; i < m_items.size(); i++)
    {
        if (x >= m_items[i].m_nWidth)
            x -= m_items[i].m_nWidth;
        else
        {
            emit wheelChanged(i, event);
            break;
        }
    }
}

void FluTimePickerViewMask::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(Qt::NoPen);

    paintBackground(painter);

    paintText(painter);
}
