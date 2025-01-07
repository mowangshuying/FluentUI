#pragma once

#include "FluWidget.h"
#include <QGridLayout>
#include <QLabel>
#include "../FluUtils/FluUtils.h"
#include "FluCalendarItem.h"

class FluCalendarView;
class FluCalendarSelectMonthView : public FluWidget
{
    Q_OBJECT
  public:
    FluCalendarSelectMonthView(QWidget* parent = nullptr);

    void setYearMonth(int nYear, int nMonth);

    void updateStyleSheet();

    QDate getPreYear();

    QDate getNextYear();

    void gotoPreYear();

    void gotoNextYear();

    FluCalendarItem* getItem(int nIndex);

  public slots:
    void onThemeChanged();

  protected:
    QGridLayout* m_gMainLayout;
    QList<FluCalendarItem*> m_labelList;
    // QDate m_curYear;
    FluCalendarView* m_parentView;
};
