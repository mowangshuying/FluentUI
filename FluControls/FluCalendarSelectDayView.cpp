#include "FluCalendarSelectDayView.h"
#include <QLabel>
#include "FluCalendarView.h"

FluCalendarViewWeakTitle::FluCalendarViewWeakTitle(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    // QLabel* m_label = new QLabel("Su");
    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setContentsMargins(10, 0, 10, 0);
    m_hMainLayout->setSpacing(0);
    setLayout(m_hMainLayout);

    QList<QString> weekTexts = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
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
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewWeakTitle.qss", this);
}

void FluCalendarViewWeakTitle::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

FluCalendarMonthView::FluCalendarMonthView(QWidget* parent /*= nullptr*/) : QWidget(parent)
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
        }
    }

    // m_calendar.init();

    setFixedHeight(270);
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarMonthView.qss", this);
}

FluCalendarItem* FluCalendarMonthView::getItem(int nIndex)
{
    return m_labelList.at(nIndex);
}

void FluCalendarMonthView::setYearMonth(int nYear, int nMonth)
{
    // QDate date = QDate::currentDate();
    // m_curMonth = QDate(nYear, nMonth, 1);

    QDate today = QDate::currentDate();
    if (nYear < 1924 || nYear > 2124)
        return;

    if (nMonth < 0 || nMonth > 12)
        return;

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

            date = date.addDays(1);
        }

        return;
    }

  //  if (nYear == 2024 && nMonth == 12)
  //  {
  //      return;
  //  }

    // QDate date(1900, 12, 24);

    QDate date(nYear, nMonth, 1);
    int day = date.dayOfWeek();

    for (int i = day; i > 0; i--)
    {
        date = date.addDays(-1);
        QString dayText = QString::asprintf("%d", date.day());
        getItem(i - 1)->setText(dayText);
        getItem(i - 1)->setInfoText("");
        getItem(i - 1)->setProperty("curMonth", false);
    }

    date = QDate(nYear, nMonth, 1);
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

        if (date.day() == 1)
        {
            // LOG_DEBUG << "the date day == 1 && " << date << ",month:" << date.month();
            QList<QString> monthTexts = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
            getItem(j)->setInfoText(monthTexts.at(date.month() - 1));
        }
        else
        {
            getItem(j)->setInfoText("");
        }

        if (date == today)
        {
            getItem(j)->setProperty("today", true);
        }

        date = date.addDays(1);
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
    setYearMonth(date.year(), date.month());
}

void FluCalendarMonthView::gotoPreMonth()
{
    QDate date = getPreMonth();
    m_calendarView->setCurDate(date);
    setYearMonth(date.year(), date.month());
}

FluCalendarSelectDayView::FluCalendarSelectDayView(QWidget* parent /*= nullptr*/) : QWidget(parent)
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
    m_monthView->setYearMonth(curDate.year(), curDate.month());
    m_parentView->getViewTitle()->setYearMonth(curDate.year(), curDate.month());
}
