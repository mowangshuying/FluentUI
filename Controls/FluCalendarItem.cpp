#include "FluCalendarItem.h"

FluCalendarItem::FluCalendarItem(QWidget* parent /*= nullptr*/) : QLabel(parent)
{
    m_infoText = QString("");
}

void FluCalendarItem::setInfoText(QString infoText)
{
    m_infoText = infoText;
    update();
}

void FluCalendarItem::setViewState(FluCalendarViewState viewState)
{
    m_viewState = viewState;
}

FluCalendarViewState FluCalendarItem::getViewState()
{
    return m_viewState;
}

QDate FluCalendarItem::getCurDate()
{
    return m_curDate;
}

void FluCalendarItem::setCurDate(QDate curDate)
{
    m_curDate = curDate;
}

void FluCalendarItem::mouseReleaseEvent(QMouseEvent* ev)
{
    QLabel::mouseReleaseEvent(ev);
    // LOG_DEBUG << "called";
    emit clicked();
}

void FluCalendarItem::paintEvent(QPaintEvent* event)
{
    QLabel::paintEvent(event);

    QPainter painter(this);
    if (m_infoText.isEmpty())
    {
        return;
    }

    QPen pen;
    pen.setBrush(QBrush(QColor(131, 131, 131)));
    painter.setPen(pen);

    QFont font;
    font.setPointSize(6);
    painter.setFont(font);
    QRect textRect(15, 6, 20, 10);
    painter.drawText(textRect, m_infoText);
}
