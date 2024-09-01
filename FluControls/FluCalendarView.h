#pragma once

#include <QCalendarWidget>
#include "FluWidget.h"
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

class FluCalendarViewTitle;
class FluCalendarSelectDayView;
class FluCalendarSelectMonthView;
class FluCalendarSelectYearView;

class FluCalendarView : public FluWidget
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

    FluCalendarViewTitle* getViewTitle();

    QDate getCurDate();

    void setCurDate(QDate date);

    FluCalendarViewState getViewState();

    void setViewState(FluCalendarViewState viewState);

    void paintEvent(QPaintEvent* event);
  signals:
    void selectedDate(QDate date);

  public slots:
    void onThemeChanged();

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
