#include "FluCalendarSelectYearView.h"
#include "FluCalendarView.h"

FluCalendarSelectYearView::FluCalendarSelectYearView(QWidget* parent) : FluWidget(parent)
{
    m_parentView = (FluCalendarView*)parent;

    m_gMainLayout = new QGridLayout;
    m_gMainLayout->setContentsMargins(10, 0, 10, 0);
    m_gMainLayout->setSpacing(0);
    m_gMainLayout->setVerticalSpacing(5);
    setLayout(m_gMainLayout);

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
            m_gMainLayout->addWidget(label, i, j);
        }
    }

    QDate curDate = m_parentView->getCurDate();
    // LOG_DEBUG << curDate;
    setYears(curDate.year(), curDate.month());

    setFixedHeight(300);
    onThemeChanged();
}

FluCalendarItem* FluCalendarSelectYearView::getItem(int nIndex)
{
    if (nIndex < 0 || nIndex >= m_labelList.size())
        return nullptr;

    return m_labelList.at(nIndex);
}

void FluCalendarSelectYearView::setYears(int nYear, int nMonth)
{
    if (nYear < 1924 || nYear > 2124)
        return;

    for (int i = 0; i < 16; i++)
    {
        getItem(i)->setText("");
    }

    // 1930 - 1939
    if (nYear < 1939)
    {
        int nStartYear = 1930;
        int nEndYear = 1939;

        m_parentView->setCurDate(QDate(nStartYear, 1, 1));  // update curDate
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
    int nStartYear = nYear - nYear % 10;
    int nEndYear = nStartYear + 9;
    if (nYear + 9 > 2124)
        nEndYear = 2124;

    m_parentView->setCurDate(QDate(nStartYear, 1, 1));  // update curDate

    // the first year;
    int nTheFirstYear = nStartYear - (nStartYear - 1924) % 4;
    for (int i = 0; i < 16; i++)
    {
        if (nTheFirstYear + i > 2124)
            break;

        getItem(i)->setText(QString::asprintf("%d", nTheFirstYear + i));
        getItem(i)->setCurDate(QDate(nTheFirstYear + i, 1, 1));

        getItem(i)->setProperty("today", false);
        if (getItem(i)->getCurDate().year() == QDate::currentDate().year())
        {
            getItem(i)->setProperty("today", true);
        }

        getItem(i)->setProperty("outRange", false);
        if ((nTheFirstYear + i < nStartYear) || (nTheFirstYear + i > nEndYear))
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

void FluCalendarSelectYearView::getRange(int nYear, int& nStartYear, int& nEndYear)
{
    if (nYear < 1924 || nYear > 2124)
        return;

    if (nYear < 1939)
    {
        nStartYear = 1930;
        nEndYear = 1939;
        return;
    }

    nStartYear = nYear - nYear % 10;

    nEndYear = nStartYear + 9;
    if (nYear + 9 > 2124)
        nEndYear = 2124;
}

void FluCalendarSelectYearView::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluCalendarSelectYearView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
