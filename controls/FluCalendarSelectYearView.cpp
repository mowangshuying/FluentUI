#include "FluCalendarSelectYearView.h"
#include "FluCalendarView.h"

FluCalendarSelectYearView::FluCalendarSelectYearView(QWidget* parent) : FluWidget(parent)
{
    m_parentView = (FluCalendarView*)parent;

    m_mainLayout = new QGridLayout;
    m_mainLayout->setContentsMargins(10, 0, 10, 0);
    m_mainLayout->setSpacing(0);
    m_mainLayout->setVerticalSpacing(5);
    setLayout(m_mainLayout);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            FluCalendarItem* label = new FluCalendarItem;
            label->setViewState(FluCVS_SelectMonthView);
            label->setObjectName("label");
            label->setFixedSize(50, 50);

            label->setText("");
            label->setAlignment(Qt::AlignCenter);
            label->setProperty("today", false);

            connect(label, &FluCalendarItem::clicked, [=]() {
                QDate itemDate = label->getCurDate();
                LOG_DEBUG << itemDate;

                setYears(itemDate.year(), itemDate.month());
                m_parentView->setCurDate(itemDate);
                m_parentView->switchSelectMonthView();

                // m_parentView->getSelectDayView()->getMonthView()->setYearMonth(itemDate.year(), itemDate.month());
                // m_parentView->getSelectMonthView()->setYearMonth(itemDate.year(), itemDate.month());
                // m_parentView->getViewTitle()->setYearMonth(itemDate.year(), itemDate.month());

                // LOG_DEBUG << "item Clicked!";
            });

            m_labelList.append(label);
            m_mainLayout->addWidget(label, i, j);
        }
    }

    QDate curDate = m_parentView->getCurDate();
    // LOG_DEBUG << curDate;
    setYears(curDate.year(), curDate.month());

    setFixedHeight(300);
    onThemeChanged();
}

FluCalendarItem* FluCalendarSelectYearView::getItem(int index)
{
    if (index < 0 || index >= m_labelList.size())
        return nullptr;

    return m_labelList.at(index);
}

void FluCalendarSelectYearView::setYears(int year, int month)
{
    if (year < 1924 || year > 2124)
        return;

    for (int i = 0; i < 16; i++)
    {
        getItem(i)->setText("");
    }

    // 1930 - 1939
    if (year < 1939)
    {
        int startYear = 1930;
        int endYear = 1939;

        m_parentView->setCurDate(QDate(startYear, 1, 1));  // update curDate
        for (int i = 0; i < 16; i++)
        {
            getItem(i)->setText(QString::asprintf("%d", 1924 + i));
            getItem(i)->setCurDate(QDate(1924 + i, 1, 1));

            getItem(i)->setProperty("today", false);
            if (getItem(i)->getCurDate().year() == QDate::currentDate().year())
            {
                getItem(i)->setProperty("today", true);
            }

            getItem(i)->setProperty("outRange", false);

            if ((1924 + i < 1930) || (1924 + i > 1939))
            {
                getItem(i)->setProperty("outRange", true);
            }
        }

        updateStyleSheet();
        return;
    }

    // other;
    int startYear = year - year % 10;
    int endYear = startYear + 9;
    if (year + 9 > 2124)
        endYear = 2124;

    m_parentView->setCurDate(QDate(startYear, 1, 1));  // update curDate

    // the first year;
    int theFirstYear = startYear - (startYear - 1924) % 4;
    for (int i = 0; i < 16; i++)
    {
        if (theFirstYear + i > 2124)
            break;

        getItem(i)->setText(QString::asprintf("%d", theFirstYear + i));
        getItem(i)->setCurDate(QDate(theFirstYear + i, 1, 1));

        getItem(i)->setProperty("today", false);
        if (getItem(i)->getCurDate().year() == QDate::currentDate().year())
        {
            getItem(i)->setProperty("today", true);
        }

        getItem(i)->setProperty("outRange", false);
        if ((theFirstYear + i < startYear) || (theFirstYear + i > endYear))
        {
            getItem(i)->setProperty("outRange", true);
        }
    }

    updateStyleSheet();
}

void FluCalendarSelectYearView::updateStyleSheet()
{
    for (int i = 0; i < m_labelList.size(); i++)
    {
        auto label = m_labelList.at(i);
        label->style()->polish(label);
    }
}

void FluCalendarSelectYearView::gotoPreYears()
{
    int curYear = m_parentView->getCurDate().year();
    curYear = curYear - curYear % 10;
    curYear -= 10;
    setYears(curYear, 1);
}

void FluCalendarSelectYearView::gotoNextYears()
{
    int curYear = m_parentView->getCurDate().year();
    curYear = curYear - curYear % 10;
    curYear += 10;
    setYears(curYear, 1);
}

void FluCalendarSelectYearView::getRange(int year, int& startYear, int& endYear)
{
    if (year < 1924 || year > 2124)
        return;

    if (year < 1939)
    {
        startYear = 1930;
        endYear = 1939;
        return;
    }

    startYear = year - year % 10;

    endYear = startYear + 9;
    if (year + 9 > 2124)
        endYear = 2124;
}

void FluCalendarSelectYearView::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluCalendarSelectYearView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
