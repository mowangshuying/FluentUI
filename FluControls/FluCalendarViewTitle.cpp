#include "FluCalendarViewTitle.h"
#include "FluCalendarView.h"

FluCalendarViewTitle::FluCalendarViewTitle(QWidget* parent /*= nullptr*/) : FluWidget(parent)
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

    // connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); }); { onThemeChanged(); });
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
