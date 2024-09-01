#pragma once

#include "FluWidget.h"
#include <QGridLayout>
#include <QLabel>
#include "../FluUtils/FluUtils.h"
#include "FluCalendarItem.h"

class FluCalendarView;

class FluCalendarSelectYearView : public FluWidget
{
  public:
    FluCalendarSelectYearView(QWidget* parent = nullptr);

    FluCalendarItem* getItem(int nIndex);

    void setYears(int nYear, int nMonth);

    void updateStyleSheet();

    void gotoPreYears();

    void gotoNextYears();

    void getRange(int nYear, int& nStartYear, int& nEndYear);

  public slots:
    void onThemeChanged();

  protected:
    QGridLayout* m_gMainLayout;
    QList<FluCalendarItem*> m_labelList;
    FluCalendarView* m_parentView;
};
