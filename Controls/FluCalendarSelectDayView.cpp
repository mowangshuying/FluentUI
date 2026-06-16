#include "FluCalendarSelectDayView.h"
#include <QLabel>
#include "FluCalendarView.h"
#include "FluCalendarViewTitle.h"

FluCalendarViewWeakTitle::FluCalendarViewWeakTitle(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    // QLabel* m_label = new QLabel("Su");
    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setContentsMargins(10, 0, 10, 0);
    m_hMainLayout->setSpacing(0);
    setLayout(m_hMainLayout);

    QList<QString> weekTexts = {tr("Su"), tr("Mo"), tr("Tu"), tr("We"), tr("Th"), tr("Fr"), tr("Sa")};
    for (int i = 0; i < weekTexts.size(); i++)
    {
        QLabel* label = new QLabel;
        // label->setFixedWidth(40);
        label->setFixedSize(40, 40);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);
        label->setText(weekTexts.at(i));

        m_hMainLayout->addWidget(label);
    }

    setFixedHeight(30);
    onThemeChanged();
}

void FluCalendarViewWeakTitle::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluCalendarViewWeakTitle::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluCalendarViewWeakTitle.qss", this, FluThemeUtils::getUtils()->getTheme());
}

FluCalendarMonthView::FluCalendarMonthView(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_gMainLayout = new QGridLayout;
    m_gMainLayout->setContentsMargins(10, 0, 10, 0);
    m_gMainLayout->setSpacing(0);
    m_gMainLayout->setVerticalSpacing(5);
    setLayout(m_gMainLayout);

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            FluCalendarItem* label = new FluCalendarItem;
            label->setViewState(FluCVS_SelectDayView);
            label->setObjectName("label");
            label->setFixedSize(40, 40);

            label->setAlignment(Qt::AlignCenter);
            label->setProperty("today", false);

            m_labelList.append(label);
            m_gMainLayout->addWidget(label, i, j);

            label->setProperty("selected", false);
            connect(label, &FluCalendarItem::clicked, [=]() {
                // clear item state;
                for (int i = 0; i < 42; i++)
                {
                    getItem(i)->setProperty("selected", false);
                    getItem(i)->style()->polish(getItem(i));
                }

                // LOG_DEBUG << "item Clicked!";
                label->setProperty("selected", true);
                label->style()->polish(label);
                // m_calendarView->setCurDate(label->getCurDate());

                // LOG_DEBUG << label->getCurDate();

                m_calendarView->setCurDate(label->getCurDate());
                emit m_calendarView->selectedDate(label->getCurDate());
            });
        }
    }

    // m_calendar.init();

    setFixedHeight(270);
    // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarMonthView.qss", this);
    onThemeChanged();
}

FluCalendarItem* FluCalendarMonthView::getItem(int nIndex)
{
    return m_labelList.at(nIndex);
}

void FluCalendarMonthView::setYearMonth(int nYear, int nMonth)
{
    QDate today = QDate::currentDate();
    if (nYear < 1924 || nYear > 2124)
        return;

    if (nMonth < 0 || nMonth > 12)
        return;

    // updateStyleSheet();
    if (nYear == 1924 && nMonth == 1)
    {
        QDate date(1924, 1, 1);
        int day = date.dayOfWeek();

        // get day
        for (int i = 0; i < 42; i++)
        {
            int j = i + day;
            if (j >= 42)
                break;

            QString dayText = QString::asprintf("%d", date.day());
            getItem(j)->setText(dayText);

            getItem(j)->setProperty("curMonth", true);
            if (date.month() != nMonth)
            {
                getItem(j)->setProperty("curMonth", false);
            }

            getItem(j)->setProperty("selected", false);
            getItem(j)->setCurDate(date);

            date = date.addDays(1);
        }

        updateStyleSheet();
        return;
    }

    QDate date(nYear, nMonth, 1);
    int day = date.dayOfWeek();

    for (int i = day; i > 0 && day != 7; i--)
    {
        date = date.addDays(-1);
        QString dayText = QString::asprintf("%d", date.day());
        getItem(i - 1)->setText(dayText);
        getItem(i - 1)->setInfoText("");
        getItem(i - 1)->setProperty("curMonth", false);
        getItem(i - 1)->setCurDate(date);
    }

    date = QDate(nYear, nMonth, 1);
    for (int i = 0; i < 42; i++)
    {
        int j = i;
        if (day != 7)
            j += day;

        if (j >= 42)
            break;

        QString dayText = QString::asprintf("%d", date.day());
        getItem(j)->setText(dayText);

        getItem(j)->setProperty("curMonth", true);
        if (date.month() != nMonth)
        {
            getItem(j)->setProperty("curMonth", false);
        }

        if (date.day() == 1)
        {
            // LOG_DEBUG << "the date day == 1 && " << date << ",month:" << date.month();
            QList<QString> monthTexts = {tr("Jan"), tr("Feb"), tr("Mar"), tr("Apr"), tr("May"), tr("Jun"), tr("Jul"), tr("Aug"), tr("Sep"), tr("Oct"), tr("Nov"), tr("Dec")};
            getItem(j)->setInfoText(monthTexts.at(date.month() - 1));
        }
        else
        {
            getItem(j)->setInfoText("");
        }

        getItem(j)->setProperty("today", false);
        if (date == today)
        {
            getItem(j)->setProperty("today", true);
        }

        getItem(j)->setProperty("selected", false);

        getItem(j)->setCurDate(date);
        date = date.addDays(1);
    }

    updateStyleSheet();
}

void FluCalendarMonthView::updateStyleSheet()
{
    for (int i = 0; i < m_labelList.size(); i++)
    {
        auto label = m_labelList.at(i);
        label->style()->polish(label);
    }
}

QDate FluCalendarMonthView::getCurMonth()
{
    return m_calendarView->getCurDate();
}

QDate FluCalendarMonthView::getNextMonth()
{
    return m_calendarView->getCurDate().addMonths(1);
}

QDate FluCalendarMonthView::getPreMonth()
{
    return m_calendarView->getCurDate().addMonths(-1);
}

void FluCalendarMonthView::gotoNextMonth()
{
    QDate date = getNextMonth();
    m_calendarView->setCurDate(date);
    setYearMonth(date.year(), date.month());  //
}

void FluCalendarMonthView::gotoPreMonth()
{
    QDate date = getPreMonth();
    m_calendarView->setCurDate(date);
    setYearMonth(date.year(), date.month());
}

void FluCalendarMonthView::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluCalendarMonthView.qss", this, FluThemeUtils::getUtils()->getTheme());
}

FluCalendarSelectDayView::FluCalendarSelectDayView(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_parentView = (FluCalendarView*)parent;
    m_vMainLayout = new QVBoxLayout;
    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    m_vMainLayout->setSpacing(0);
    setLayout(m_vMainLayout);

    m_weekTitle = new FluCalendarViewWeakTitle(this);
    m_vMainLayout->addWidget(m_weekTitle);

    m_monthView = new FluCalendarMonthView(this);
    m_monthView->setCalendarView(m_parentView);
    m_vMainLayout->addWidget(m_monthView);

    QDate curDate = m_parentView->getCurDate();
    //  LOG_DEBUG << curDate;
    m_monthView->setYearMonth(curDate.year(), curDate.month());
    m_parentView->getViewTitle()->setYearMonth(curDate.year(), curDate.month());
}

void FluCalendarSelectDayView::gotoNextMonth()
{
    m_monthView->gotoNextMonth();
}

void FluCalendarSelectDayView::gotoPreMonth()
{
    m_monthView->gotoPreMonth();
}

QDate FluCalendarSelectDayView::getCurMonth()
{
    return m_monthView->getCurMonth();
}

void FluCalendarSelectDayView::setParentView(FluCalendarView* view)
{
    m_parentView = view;
}

FluCalendarViewWeakTitle* FluCalendarSelectDayView::getWeekTitle()
{
    return m_weekTitle;
}

FluCalendarMonthView* FluCalendarSelectDayView::getMonthView()
{
    return m_monthView;
}
