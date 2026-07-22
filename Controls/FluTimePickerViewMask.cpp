#include "FluTimePickerViewMask.h"

FluTimePickerViewMaskItem::FluTimePickerViewMaskItem(QString text, int width, int height)
{
    m_text = text;
    m_width = width;
    m_height = height;
}

FluTimePickerViewMask::FluTimePickerViewMask(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_curIndex = -1;
    setMouseTracking(true);
}

void FluTimePickerViewMask::addItem(QString text, int w, int h)
{
    FluTimePickerViewMaskItem item(text, w, h);
    m_items.push_back(item);
}

void FluTimePickerViewMask::setItemText(int index, QString text)
{
    m_items[index].m_text = text;
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

    int x = 0;
    int y = 0;
    for (auto item : m_items)
    {
        painter.drawText(QRect(x, y, item.m_width, item.m_height), Qt::AlignCenter, item.m_text);
        x += item.m_width;
    }
}

void FluTimePickerViewMask::mouseMoveEvent(QMouseEvent* event)
{
    // LOG_DEBUG << "called";
    int x = mapFromGlobal(QCursor().pos()).x();
    // LOG_DEBUG << "x:" << x;

    int tmpIndex = -1;
    for (int i = 0; i < m_items.size(); i++)
    {
        if (x >= m_items[i].m_width)
        {
            x -= m_items[i].m_width;
        }
        else
        {
            tmpIndex = i;
            break;
        }
    }

    if (m_curIndex == -1 || m_curIndex == tmpIndex)
    {
        m_curIndex = tmpIndex;

        QPointF localP;
        QPointF senceP;
        QPointF globalP;
        QEnterEvent tmpEvent(localP, senceP, globalP);
        emit enterChanged(m_curIndex, &tmpEvent);
        return;
    }

    if (m_curIndex != tmpIndex)
    {
        QEvent tmpLeaveEvent(QEvent::Leave);
        emit leaveChanged(m_curIndex, &tmpLeaveEvent);

        QPointF localP;
        QPointF senceP;
        QPointF globalP;
        QEnterEvent tmpEnterEvent(localP, senceP, globalP);
        emit enterChanged(tmpIndex, &tmpEnterEvent);

        m_curIndex = tmpIndex;
    }
}

void FluTimePickerViewMask::wheelEvent(QWheelEvent* event)
{
    int x = mapFromGlobal(QCursor().pos()).x();
    for (int i = 0; i < m_items.size(); i++)
    {
        if (x >= m_items[i].m_width)
            x -= m_items[i].m_width;
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
