#pragma once

#include "FluWidget.h"
#include <QGridLayout>
#include <QLabel>
#include "../Utils/FluUtils.h"
#include "FluCalendarItem.h"

class FluCalendarView;
class FluCalendarSelectMonthView : public FluWidget
{
    Q_OBJECT
  public:
    FluCalendarSelectMonthView(QWidget* parent = nullptr);

    void setYearMonth(int year, int month);

    void updateStyleSheet();

    QDate getPreYear();

    QDate getNextYear();

    void gotoPreYear();

    void gotoNextYear();

    FluCalendarItem* getItem(int index);

  public slots:
    void onThemeChanged();

  protected:
    QGridLayout* m_mainLayout;
    QList<FluCalendarItem*> m_labelList;
    // QDate m_curYear;
    FluCalendarView* m_parentView;
};
