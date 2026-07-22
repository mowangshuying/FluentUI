#pragma once

#include "FluWidget.h"
#include <QGridLayout>
#include <QLabel>
#include "../Utils/FluUtils.h"
#include "FluCalendarItem.h"

class FluCalendarView;

class FluCalendarSelectYearView : public FluWidget
{
  public:
    FluCalendarSelectYearView(QWidget* parent = nullptr);

    FluCalendarItem* getItem(int index);

    void setYears(int year, int month);

    void updateStyleSheet();

    void gotoPreYears();

    void gotoNextYears();

    void getRange(int year, int& startYear, int& endYear);

  public slots:
    void onThemeChanged();

  protected:
    QGridLayout* m_mainLayout;
    QList<FluCalendarItem*> m_labelList;
    FluCalendarView* m_parentView;
};
