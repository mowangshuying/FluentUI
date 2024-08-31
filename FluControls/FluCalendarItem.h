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
    FluCalendarItem(QWidget* parent = nullptr);

    void setInfoText(QString infoText);

    void setViewState(FluCalendarViewState viewState);

    FluCalendarViewState getViewState();

    QDate getCurDate();

    void setCurDate(QDate curDate);

    void mouseReleaseEvent(QMouseEvent* ev);

    void paintEvent(QPaintEvent* event);
  signals:
    void clicked();

  protected:
    QString m_infoText;
    FluCalendarViewState m_viewState;
    QDate m_curDate;
};
