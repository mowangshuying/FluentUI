#pragma once

#include "FluPushButton.h"
#include "FluWidget.h"
#include "FluIconButton.h"
#include <QStyleOption>
#include <QPainter>

class FluCalendarView;
class FluCalendarViewTitle : public FluWidget
{
    Q_OBJECT
  public:
    FluCalendarViewTitle(QWidget* parent = nullptr);

    FluPushButton* getYearMonthButton();

    FluIconButton* getNextButton();

    FluIconButton* getPreviousButton();

    void setYearMonth(int year, int month);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    FluPushButton* m_yearMonthButton;
    FluIconButton* m_previousMonthButton;
    FluIconButton* m_nextMonthButton;

    QHBoxLayout* m_titleLayout;

    FluCalendarView* m_parentView;
};