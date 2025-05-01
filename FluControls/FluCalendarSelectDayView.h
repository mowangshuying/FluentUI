#pragma once

// #include "FluCalendarView.h"
#include "FluWidget.h"
#include <QVBoxLayout>
#include <QDate>
#include <QPaintEvent>
#include <QPainter>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include "FluCalendarDef.h"
#include "FluCalendarItem.h"
#include "FluCalendarView.h"
#include "FluWidget.h"

class FluCalendarView;
class FluCalendarViewWeakTitle : public FluWidget
{
    Q_OBJECT
  public:
    FluCalendarViewWeakTitle(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

  public slots:
    void onThemeChanged();

  protected:
    QHBoxLayout* m_hMainLayout;
};

class FluCalendarMonthView : public FluWidget
{
    Q_OBJECT
  public:
    FluCalendarMonthView(QWidget* parent = nullptr);

    void setCalendarView(FluCalendarView* view)
    {
        m_calendarView = view;
    }

    FluCalendarItem* getItem(int nIndex);

    void setYearMonth(int nYear, int nMonth);

    void updateStyleSheet();

    QDate getCurMonth();

    QDate getNextMonth();

    QDate getPreMonth();

    void gotoNextMonth();

    void gotoPreMonth();

  signals:
    void curMonthChanged();
  public slots:
    void onThemeChanged();

  protected:
    QGridLayout* m_gMainLayout;
    QList<FluCalendarItem*> m_labelList;
    FluCalendarView* m_calendarView;
};

class FluCalendarSelectDayView : public FluWidget
{
    Q_OBJECT
  public:
    FluCalendarSelectDayView(QWidget* parent = nullptr);

    void gotoNextMonth();

    void gotoPreMonth();

    QDate getCurMonth();

    void setParentView(FluCalendarView* view);

    FluCalendarViewWeakTitle* getWeekTitle();

    FluCalendarMonthView* getMonthView();

  public slots:
  protected:
    QVBoxLayout* m_vMainLayout;

    FluCalendarViewWeakTitle* m_weekTitle;  // weakTitle;
    FluCalendarMonthView* m_monthView;      // monthView;
    FluCalendarView* m_parentView;          // parentView;
};