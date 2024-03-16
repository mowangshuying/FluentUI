#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "../FluUtils/FluUtils.h"
#include "FluCalendarItem.h"

class FluCalendarView;
class FluCalendarSelectMonthView : public QWidget
{
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
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarSelectMonthView.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCalendarSelectMonthView.qss", this);
        }
    }

  protected:
    QGridLayout* m_gMainLayout;
    QList<FluCalendarItem*> m_labelList;
    // QDate m_curYear;
    FluCalendarView* m_parentView;
};
