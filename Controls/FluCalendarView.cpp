#include "FluCalendarView.h"
#include "FluCalendarSelectDayView.h"
#include "FluCalendarSelectMonthView.h"
#include "FluCalendarSelectYearView.h"
#include "FluCalendarViewTitle.h"
#include "FluVSplitLine.h"

FluCalendarView::FluCalendarView(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_currentDate = QDate::currentDate();
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setContentsMargins(1, 1, 1, 1);
    m_mainLayout->setSpacing(0);

    setLayout(m_mainLayout);
    m_title = new FluCalendarViewTitle(this);
    m_mainLayout->addWidget(m_title);

    m_mainLayout->addWidget(new FluVSplitLine, 0, Qt::AlignTop);

    m_viewSwitchLayout = new QStackedLayout;
    m_mainLayout->addLayout(m_viewSwitchLayout);

    m_selectDayView = new FluCalendarSelectDayView(this);
    m_viewSwitchLayout->addWidget(m_selectDayView);

    m_selectMonthView = new FluCalendarSelectMonthView(this);
    m_viewSwitchLayout->addWidget(m_selectMonthView);

    m_selectYearView = new FluCalendarSelectYearView(this);
    m_viewSwitchLayout->addWidget(m_selectYearView);

    m_viewState = FluCVS_SelectDayView;

    m_currentDate = QDate::currentDate();
    m_title->setYearMonth(m_currentDate.year(), m_currentDate.month());
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

    connect(m_title->getPreviousButton(), &FluIconButton::clicked, [=](bool bClicked) {
        if (m_viewState == FluCVS_SelectDayView)
        {
            m_selectDayView->gotoPreMonth();
            m_title->setYearMonth(m_currentDate.year(), m_currentDate.month());
            return;
        }

        if (m_viewState == FluCVS_SelectMonthView)
        {
            m_selectMonthView->gotoPreYear();
            m_title->setYearMonth(m_currentDate.year(), m_currentDate.month());
            return;
        }

        if (m_viewState == FluCVS_SelectYearView)
        {
            m_selectYearView->gotoPreYears();

            int nStartYears = 0;
            int nEndYears = 0;
            m_selectYearView->getRange(m_currentDate.year(), nStartYears, nEndYears);
            m_title->setYearMonth(nStartYears, nEndYears);
        }
    });

    connect(m_title->getNextButton(), &FluIconButton::clicked, [=](bool bClicked) {
        if (m_viewState == FluCVS_SelectDayView)
        {
            m_selectDayView->gotoNextMonth();
            QDate date = m_selectDayView->getCurMonth();
            m_title->setYearMonth(date.year(), date.month());
            return;
        }

        if (m_viewState == FluCVS_SelectMonthView)
        {
            m_selectMonthView->gotoNextYear();
            m_title->setYearMonth(m_currentDate.year(), m_currentDate.month());
            return;
        }

        if (m_viewState == FluCVS_SelectYearView)
        {
            m_selectYearView->gotoNextYears();
            int nStartYears = 0;
            int nEndYears = 0;
            m_selectYearView->getRange(m_currentDate.year(), nStartYears, nEndYears);
            m_title->setYearMonth(nStartYears, nEndYears);
        }
    });

    setFixedSize(300, 360);
    onThemeChanged();
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
    m_selectMonthView->setYearMonth(m_currentDate.year(), m_currentDate.month());
    m_title->setYearMonth(m_currentDate.year(), m_currentDate.month());
    m_viewSwitchLayout->setCurrentWidget(m_selectMonthView);
}

void FluCalendarView::switchSelectYearView()
{
    m_viewState = FluCVS_SelectYearView;

    int nStartYear = 0;
    int nEndYear = 0;

    m_selectYearView->getRange(m_currentDate.year(), nStartYear, nEndYear);
    m_title->setYearMonth(nStartYear, nEndYear);
    m_selectYearView->setYears(m_currentDate.year(), m_currentDate.month());
    m_viewSwitchLayout->setCurrentWidget(m_selectYearView);
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

FluCalendarViewTitle* FluCalendarView::getViewTitle()
{
    return m_title;
}

QDate FluCalendarView::getCurDate()
{
    return m_currentDate;
}

void FluCalendarView::setCurDate(QDate date)
{
    m_currentDate = date;
}

FluCalendarViewState FluCalendarView::getViewState()
{
    return m_viewState;
}

void FluCalendarView::setViewState(FluCalendarViewState viewState)
{
    m_viewState = viewState;
}

void FluCalendarView::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluCalendarView::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluCalendarView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
