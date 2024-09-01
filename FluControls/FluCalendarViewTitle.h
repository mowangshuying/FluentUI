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

    FluPushButton* getYearMonthBtn();

    FluIconButton* getNextBtn();

    FluIconButton* getPreBtn();

    void setYearMonth(int nYear, int nMonth);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    FluPushButton* m_yearMonthBtn;
    FluIconButton* m_preBtn;
    FluIconButton* m_nextBtn;

    QHBoxLayout* m_hMainLayout;

    FluCalendarView* m_parentView;
};