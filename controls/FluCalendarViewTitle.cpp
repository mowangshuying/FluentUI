#include "FluCalendarViewTitle.h"
#include "FluCalendarView.h"

FluCalendarViewTitle::FluCalendarViewTitle(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_parentView = (FluCalendarView*)parent;
    m_titleLayout = new QHBoxLayout;
    setLayout(m_titleLayout);

    m_yearMonthButton = new FluPushButton;
    m_yearMonthButton->setText(tr("January 2000"));
    m_titleLayout->addWidget(m_yearMonthButton);

    m_previousMonthButton = new FluIconButton(FluAwesomeType::CaretSolidUp);
    m_nextMonthButton = new FluIconButton(FluAwesomeType::CaretSolidDown);

    m_titleLayout->addWidget(m_previousMonthButton);
    m_titleLayout->addWidget(m_nextMonthButton);

    m_yearMonthButton->setObjectName("yearMonthBtn");
    m_previousMonthButton->setObjectName("previousMonthBtn");
    m_nextMonthButton->setObjectName("nextMonthBtn");

    setFixedHeight(50);
    onThemeChanged();
}

FluPushButton* FluCalendarViewTitle::getYearMonthButton()
{
    return m_yearMonthButton;
}

FluIconButton* FluCalendarViewTitle::getNextButton()
{
    return m_nextMonthButton;
}

FluIconButton* FluCalendarViewTitle::getPreviousButton()
{
    return m_previousMonthButton;
}

void FluCalendarViewTitle::setYearMonth(int year, int month)
{
    if (year > 2124 || year < 1924)
        return;

    const QList<QString> monthTexts = {tr("January"), tr("February"), tr("March"), tr("April"), tr("May"), tr("June"), tr("July"), tr("August"), tr("September"), tr("October"), tr("November"), tr("December")};
    if (m_parentView->getViewState() == FluCVS_SelectDayView)
    {
        QString yearMonthText = QString::asprintf("%s %d", monthTexts.at(month - 1).toUtf8().data(), year);
        m_yearMonthButton->setText(yearMonthText);
    }
    else if (m_parentView->getViewState() == FluCVS_SelectMonthView)
    {
        QString yearMonthText = QString::asprintf("%d", year);
        m_yearMonthButton->setText(yearMonthText);
    }
    else if (m_parentView->getViewState() == FluCVS_SelectYearView)
    {
        QString yearMonthText = QString::asprintf("%d - %d", year, month);
        m_yearMonthButton->setText(yearMonthText);
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
    FluStyleSheetUtils::setQssByFileName("FluCalendarViewTitle.qss", m_yearMonthButton, FluThemeUtils::getUtils()->getTheme());
    FluStyleSheetUtils::setQssByFileName("FluCalendarViewTitle.qss", m_previousMonthButton, FluThemeUtils::getUtils()->getTheme());
    FluStyleSheetUtils::setQssByFileName("FluCalendarViewTitle.qss", m_nextMonthButton, FluThemeUtils::getUtils()->getTheme());
    FluStyleSheetUtils::setQssByFileName("FluCalendarViewTitle.qss", this, FluThemeUtils::getUtils()->getTheme());
}
