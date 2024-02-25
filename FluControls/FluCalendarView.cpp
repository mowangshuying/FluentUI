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

    m_title = new FluCalendarViewTitle;
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
            QDate date = m_selectDayView->getCurMonth();
            m_title->setYearMonth(date.year(), date.month());
        }
    });

    connect(m_title->getNextBtn(), &FluIconButton::clicked, [=](bool bClicked) {
        if (m_viewState == FluCVS_SelectDayView)
        {
            // m_selectDayView
            m_selectDayView->gotoNextMonth();
            QDate date = m_selectDayView->getCurMonth();
            m_title->setYearMonth(date.year(), date.month());
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
    m_sLayout->setCurrentWidget(m_selectDayView);
}

void FluCalendarView::switchSelectMonthView()
{
    m_sLayout->setCurrentWidget(m_selectMonthView);
}

void FluCalendarView::switchSelectYearView()
{
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
