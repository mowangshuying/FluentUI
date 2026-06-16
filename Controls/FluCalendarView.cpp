#include "FluCalendarView.h"
#include "FluCalendarSelectDayView.h"
#include "FluCalendarSelectMonthView.h"
#include "FluCalendarSelectYearView.h"
#include "FluCalendarViewTitle.h"
#include "FluVSplitLine.h"

FluCalendarView::FluCalendarView(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setWindowFlags(/* Qt::Popup | */ Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_curDate = QDate::currentDate();
    // LOG_DEBUG << m_curDate;
    m_vMainLayout = new QVBoxLayout;
    m_vMainLayout->setContentsMargins(1, 1, 1, 1);
    m_vMainLayout->setSpacing(0);

    setLayout(m_vMainLayout);
    m_title = new FluCalendarViewTitle(this);
    m_vMainLayout->addWidget(m_title);

    m_vMainLayout->addWidget(new FluVSplitLine, 0, Qt::AlignTop);

    m_sLayout = new QStackedLayout;
    m_vMainLayout->addLayout(m_sLayout);

    m_selectDayView = new FluCalendarSelectDayView(this);
    m_sLayout->addWidget(m_selectDayView);

    m_selectMonthView = new FluCalendarSelectMonthView(this);
    m_sLayout->addWidget(m_selectMonthView);

    m_selectYearView = new FluCalendarSelectYearView(this);
    m_sLayout->addWidget(m_selectYearView);

    m_viewState = FluCVS_SelectDayView;

    // LOG_DEBUG << m_curDate;
    m_curDate = QDate::currentDate();
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

    // setFixedWidth(300);
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

FluCalendarViewTitle* FluCalendarView::getViewTitle()
{
    return m_title;
}

QDate FluCalendarView::getCurDate()
{
    return m_curDate;
}

void FluCalendarView::setCurDate(QDate date)
{
    m_curDate = date;
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
    FluStyleSheetUitls::setQssByFileName("FluCalendarView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
