#pragma once

#include <QCalendarWidget>
#include <QWidget>
#include "../FluUtils/FluUtils.h"
#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QHBoxLayout>
#include "FluPushButton.h"
#include "FluIconButton.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>
#include "FluCalendarDef.h"
#include <QScrollBar>
#include <QStackedLayout>

class FluCalendarView;
class FluCalendarViewTitle : public QWidget
{
    Q_OBJECT
  public:
    FluCalendarViewTitle(QWidget* parent = nullptr);

    FluPushButton* getYearMonthBtn()
    {
        return m_yearMonthBtn;
    }

    FluIconButton* getNextBtn()
    {
        return m_nextBtn;
    }

    FluIconButton* getPreBtn()
    {
        return m_preBtn;
    }

    void setYearMonth(int nYear, int nMonth);

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  protected:
    FluPushButton* m_yearMonthBtn;
    FluIconButton* m_preBtn;
    FluIconButton* m_nextBtn;

    QHBoxLayout* m_hMainLayout;

    FluCalendarView* m_parentView;
};

class FluCalendarSelectDayView;
class FluCalendarSelectMonthView;
class FluCalendarSelectYearView;

class FluCalendarView : public QWidget
{
    Q_OBJECT
  public:
    FluCalendarView(QWidget* parent = nullptr);

    void switchSelectViewState(FluCalendarViewState state);

    void switchSelectDayView();

    void switchSelectMonthView();

    void switchSelectYearView();

    FluCalendarSelectDayView* getSelectDayView();

    FluCalendarSelectMonthView* getSelectMonthView();

    FluCalendarSelectYearView* getSelectYearView();

    FluCalendarViewTitle* getViewTitle()
    {
        return m_title;
    }

    QDate getCurDate()
    {
        return m_curDate;
    }

    void setCurDate(QDate date)
    {
        m_curDate = date;
    }

    FluCalendarViewState getViewState()
    {
        return m_viewState;
    }

    void setViewState(FluCalendarViewState viewState)
    {
        m_viewState = viewState;
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  protected:
    QDate m_curDate;
    FluCalendarViewState m_viewState;

    QVBoxLayout* m_vMainLayout;
    QStackedLayout* m_sLayout;

    FluCalendarViewTitle* m_title;
    FluCalendarSelectDayView* m_selectDayView;
    FluCalendarSelectMonthView* m_selectMonthView;
    FluCalendarSelectYearView* m_selectYearView;
};
