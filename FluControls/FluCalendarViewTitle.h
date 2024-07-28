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
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", m_yearMonthBtn);
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", m_preBtn);
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", m_nextBtn);
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCalendarViewTitle.qss", m_yearMonthBtn);
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCalendarViewTitle.qss", m_preBtn);
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCalendarViewTitle.qss", m_nextBtn);
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCalendarViewTitle.qss", this);
        }
    }

  protected:
    FluPushButton* m_yearMonthBtn;
    FluIconButton* m_preBtn;
    FluIconButton* m_nextBtn;

    QHBoxLayout* m_hMainLayout;

    FluCalendarView* m_parentView;
};