#include "FluCalendarViewTitle.h"
#include "FluCalendarView.h"

FluCalendarViewTitle::FluCalendarViewTitle(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_parentView = (FluCalendarView*)parent;
    m_hMainLayout = new QHBoxLayout;
    setLayout(m_hMainLayout);

    m_yearMonthBtn = new FluPushButton;
    m_yearMonthBtn->setText(tr("January 2000"));
    m_hMainLayout->addWidget(m_yearMonthBtn);

    m_preBtn = new FluIconButton(FluAwesomeType::CaretSolidUp);
    m_nextBtn = new FluIconButton(FluAwesomeType::CaretSolidDown);

    m_hMainLayout->addWidget(m_preBtn);
    m_hMainLayout->addWidget(m_nextBtn);

    m_yearMonthBtn->setObjectName("yearMonthBtn");
    m_preBtn->setObjectName("preBtn");
    m_nextBtn->setObjectName("nextBtn");

    setFixedHeight(50);
    onThemeChanged();
}

FluPushButton* FluCalendarViewTitle::getYearMonthBtn()
{
    return m_yearMonthBtn;
}

FluIconButton* FluCalendarViewTitle::getNextBtn()
{
    return m_nextBtn;
}

FluIconButton* FluCalendarViewTitle::getPreBtn()
{
    return m_preBtn;
}

void FluCalendarViewTitle::setYearMonth(int nYear, int nMonth)
{
    if (nYear > 2124 || nYear < 1924)
        return;

    const QList<QString> monthTexts = {tr("January"), tr("February"), tr("March"), tr("April"), tr("May"), tr("June"), tr("July"), tr("August"), tr("September"), tr("October"), tr("November"), tr("December")};
    if (m_parentView->getViewState() == FluCVS_SelectDayView)
    {
        QString yearMonthText = QString::asprintf("%s %d", monthTexts.at(nMonth - 1).toUtf8().data(), nYear);
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

void FluCalendarViewTitle::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluCalendarViewTitle::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluCalendarViewTitle.qss", m_yearMonthBtn, FluThemeUtils::getUtils()->getTheme());
    FluStyleSheetUitls::setQssByFileName("FluCalendarViewTitle.qss", m_preBtn, FluThemeUtils::getUtils()->getTheme());
    FluStyleSheetUitls::setQssByFileName("FluCalendarViewTitle.qss", m_nextBtn, FluThemeUtils::getUtils()->getTheme());
    FluStyleSheetUitls::setQssByFileName("FluCalendarViewTitle.qss", this, FluThemeUtils::getUtils()->getTheme());
}
