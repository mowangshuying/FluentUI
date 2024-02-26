#pragma once

#include <QLabel>
#include <QPainter>
#include <QFont>
// #include "FluCalendarView.h"
#include "FluCalendarDef.h"

class FluCalendarItem : public QLabel
{
    Q_OBJECT
  public:
    FluCalendarItem(QWidget* parent = nullptr) : QLabel(parent)
    {
        m_infoText = QString("");
    }

    void setInfoText(QString infoText)
    {
        m_infoText = infoText;
        update();
    }

    void setViewState(FluCalendarViewState viewState)
    {
        m_viewState = viewState;
    }

    FluCalendarViewState getViewState()
    {
        return m_viewState;
    }


    QDate getCurDate()
    {
        return m_curDate;
    }

    void setCurDate(QDate curDate)
    {
        m_curDate = curDate;
    }

    void mouseReleaseEvent(QMouseEvent* ev)
    {
        QLabel::mouseReleaseEvent(ev);
        LOG_DEBUG << "called";
        emit clicked();
    }

    void paintEvent(QPaintEvent* event)
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
  signals:
    void clicked();
  protected:
    QString m_infoText;
    FluCalendarViewState m_viewState;
    QDate m_curDate;
};
