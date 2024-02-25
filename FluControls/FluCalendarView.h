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

class FluCalendarViewTitle : public QWidget
{
    Q_OBJECT
  public:
    FluCalendarViewTitle(QWidget* parent = nullptr) : QWidget(parent)
    {
        m_hMainLayout = new QHBoxLayout;
        setLayout(m_hMainLayout);

        m_yearMonthBtn = new FluPushButton;
        m_yearMonthBtn->setText("January 2000");
        m_hMainLayout->addWidget(m_yearMonthBtn);

        m_preBtn = new FluIconButton(FluAwesomeType::CaretSolidUp);
        m_nextBtn = new FluIconButton(FluAwesomeType::CaretSolidDown);

        m_hMainLayout->addWidget(m_preBtn);
        m_hMainLayout->addWidget(m_nextBtn);

        m_yearMonthBtn->setObjectName("yearMonthBtn");
        m_preBtn->setObjectName("preBtn");
        m_nextBtn->setObjectName("nextBtn");

        setFixedHeight(50);

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", m_yearMonthBtn);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", m_preBtn);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", m_nextBtn);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", this);
    }

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

    void setYearMonth(int nYear, int nMonth)
    {
        const QList<QString> monthTexts = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        QString yearMonthText = QString::asprintf("%s %d", monthTexts.at(nMonth - 1).toStdString().data(), nYear);
        m_yearMonthBtn->setText(yearMonthText);
    }

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
