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
        QRect textRect(15, 6, 16, 10);
        painter.drawText(textRect, m_infoText);
    }

    void setInfoText(QString infoText)
    {
        m_infoText = infoText;
    }

    void setViewState(FluCalendarViewState viewState)
    {
        m_viewState = viewState;
        // setProperty("viewState", viewState);
    }

    FluCalendarViewState getViewState()
    {
        return m_viewState;
    }

    // void setDate(QDate date)
    //{
    // m_date = date;
    //}

    // QDate getDate()
    //{
    // return m_date;
    //}

  protected:
    QString m_infoText;
    FluCalendarViewState m_viewState;
    // QDate m_date;
};
