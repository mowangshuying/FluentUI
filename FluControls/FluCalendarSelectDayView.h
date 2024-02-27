#pragma once

// #include "FluCalendarView.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QDate>
#include <QPaintEvent>
#include <QPainter>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include "FluCalendarDef.h"
#include "FluCalendarItem.h"
#include "FluCalendarView.h"

class FluCalendarView;
class FluCalendarViewWeakTitle : public QWidget
{
  public:
    FluCalendarViewWeakTitle(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

  protected:
    QHBoxLayout* m_hMainLayout;
};

class FluCalendarMonthView : public QWidget
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

    //  void setCurMonth(int nYear, int nMonth)
    //  {
    // m_curMonth = QDate(nYear, nMonth, 1);
    //  }

    QDate getCurMonth();

    // void setCurMonth(QDate curMonth)
    //{
    //     LOG_DEBUG << "setCurMonth:" << curMonth;
    //     m_curMonth = curMonth;
    //     emit curMonthChanged();
    // }

    QDate getNextMonth();

    QDate getPreMonth();

    void gotoNextMonth();

    void gotoPreMonth();

  signals:
    void curMonthChanged();

  protected:
    QGridLayout* m_gMainLayout;
    QList<FluCalendarItem*> m_labelList;
    FluCalendarView* m_calendarView;
};

class FluCalendarSelectDayView : public QWidget
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

  protected:
    QVBoxLayout* m_vMainLayout;

    FluCalendarViewWeakTitle* m_weekTitle;  // weakTitle;
    FluCalendarMonthView* m_monthView;      // monthView;
    FluCalendarView* m_parentView;          // parentView;
};