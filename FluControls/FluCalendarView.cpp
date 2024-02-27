#include "FluCalendarView.h"
#include "FluCalendarSelectDayView.h"
#include "FluCalendarSelectMonthView.h"
#include "FluCalendarSelectYearView.h"

FluCalendarView::FluCalendarView(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_curDate = QDate::currentDate();
    m_vMainLayout = new QVBoxLayout;
    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    m_vMainLayout->setSpacing(0);

    setLayout(m_vMainLayout);

    m_title = new FluCalendarViewTitle(this);
    m_vMainLayout->addWidget(m_title);

    m_sLayout = new QStackedLayout;
    m_vMainLayout->addLayout(m_sLayout);

    m_selectDayView = new FluCalendarSelectDayView(this);
    m_sLayout->addWidget(m_selectDayView);

    m_selectMonthView = new FluCalendarSelectMonthView(this);
    m_sLayout->addWidget(m_selectMonthView);

    m_selectYearView = new FluCalendarSelectYearView(this);
    m_sLayout->addWidget(m_selectYearView);

    m_viewState = FluCVS_SelectDayView;

    LOG_DEBUG << m_curDate;
    m_title->setYearMonth(m_curDate.year(), m_curDate.month());
    connect(m_title->getYearMonthBtn(), &FluPushButton::clicked, [=](bool bClicked) {
        switch (m_viewState)
        {
            case FluCVS_SelectDayView:
                switchSelectMonthView();
                m_viewState = FluCVS_SelectMonthView;
                break;
            case FluCVS_SelectMonthView:
                switchSelectYearView();
                m_viewState = FluCVS_SelectYearView;
                break;
            case FluCVS_SelectYearView:
                break;
            default:
                break;
        }
    });

    connect(m_title->getPreBtn(), &FluIconButton::clicked, [=](bool bClicked) {
        if (m_viewState == FluCVS_SelectDayView)
        {
            // m_selectDayView
            m_selectDayView->gotoPreMonth();
            m_title->setYearMonth(m_curDate.year(), m_curDate.month());
            return;
        }

        if (m_viewState == FluCVS_SelectMonthView)
        {
            m_selectMonthView->gotoPreYear();
            m_title->setYearMonth(m_curDate.year(), m_curDate.month());
            return;
        }

        if (m_viewState == FluCVS_SelectYearView)
        {
            m_selectYearView->gotoPreYears();

            int nStartYears = 0;
            int nEndYears = 0;
            m_selectYearView->getRange(m_curDate.year(), nStartYears, nEndYears);
            m_title->setYearMonth(nStartYears, nEndYears);
        }
    });

    connect(m_title->getNextBtn(), &FluIconButton::clicked, [=](bool bClicked) {
        if (m_viewState == FluCVS_SelectDayView)
        {
            // m_selectDayView
            m_selectDayView->gotoNextMonth();
            QDate date = m_selectDayView->getCurMonth();
            m_title->setYearMonth(date.year(), date.month());
            return;
        }

        if (m_viewState == FluCVS_SelectMonthView)
        {
            m_selectMonthView->gotoNextYear();
            m_title->setYearMonth(m_curDate.year(), m_curDate.month());
            return;
        }

        if (m_viewState == FluCVS_SelectYearView)
        {
            m_selectYearView->gotoNextYears();
            int nStartYears = 0;
            int nEndYears = 0;
            m_selectYearView->getRange(m_curDate.year(), nStartYears, nEndYears);
            m_title->setYearMonth(nStartYears, nEndYears);
        }
    });

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarView.qss", this);
}

void FluCalendarView::switchSelectViewState(FluCalendarViewState state)
{
    switch (state)
    {
        case FluCVS_SelectDayView:
            switchSelectDayView();
            break;
        case FluCVS_SelectMonthView:
            switchSelectMonthView();
            break;
        case FluCVS_SelectYearView:
            switchSelectYearView();
            break;
        default:
            break;
    }
}

void FluCalendarView::switchSelectDayView()
{
    m_viewState = FluCVS_SelectDayView;
    m_sLayout->setCurrentWidget(m_selectDayView);
}

void FluCalendarView::switchSelectMonthView()
{
    m_viewState = FluCVS_SelectMonthView;
    m_selectMonthView->setYearMonth(m_curDate.year(), m_curDate.month());
    m_title->setYearMonth(m_curDate.year(), m_curDate.month());
    m_sLayout->setCurrentWidget(m_selectMonthView);
}

void FluCalendarView::switchSelectYearView()
{
    m_viewState = FluCVS_SelectYearView;

    int nStartYear = 0;
    int nEndYear = 0;

    m_selectYearView->getRange(m_curDate.year(), nStartYear, nEndYear);
    m_title->setYearMonth(nStartYear, nEndYear);
    m_selectYearView->setYears(m_curDate.year(), m_curDate.month());
    m_sLayout->setCurrentWidget(m_selectYearView);
}

FluCalendarSelectDayView* FluCalendarView::getSelectDayView()
{
    return m_selectDayView;
}

FluCalendarSelectMonthView* FluCalendarView::getSelectMonthView()
{
    return m_selectMonthView;
}

FluCalendarSelectYearView* FluCalendarView::getSelectYearView()
{
    return m_selectYearView;
}

FluCalendarViewTitle::FluCalendarViewTitle(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_parentView = (FluCalendarView*)parent;
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

void FluCalendarViewTitle::setYearMonth(int nYear, int nMonth)
{
    if (nYear > 2124 || nYear < 1924)
        return;

    const QList<QString> monthTexts = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    if (m_parentView->getViewState() == FluCVS_SelectDayView)
    {
        QString yearMonthText = QString::asprintf("%s %d", monthTexts.at(nMonth - 1).toStdString().data(), nYear);
        m_yearMonthBtn->setText(yearMonthText);
    }
    else if (m_parentView->getViewState() == FluCVS_SelectMonthView)
    {
        QString yearMonthText = QString::asprintf("%d", nYear);
        m_yearMonthBtn->setText(yearMonthText);
    }
    else if (m_parentView->getViewState() == FluCVS_SelectYearView)
    {
        QString yearMonthText = QString::asprintf("%d - %d", nYear, nMonth);
        m_yearMonthBtn->setText(yearMonthText);
    }
}
