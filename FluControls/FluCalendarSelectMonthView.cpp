#include "FluCalendarSelectMonthView.h"
#include "FluCalendarView.h"
#include <QDate>
#include "FluCalendarSelectDayView.h"
#include "FluCalendarViewTitle.h"

FluCalendarSelectMonthView::FluCalendarSelectMonthView(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_parentView = (FluCalendarView*)parent;

    m_gMainLayout = new QGridLayout;
    m_gMainLayout->setContentsMargins(10, 0, 10, 0);
    m_gMainLayout->setSpacing(0);
    m_gMainLayout->setVerticalSpacing(5);
    setLayout(m_gMainLayout);

    QList<QString> monthTexts = {tr("Jan"), tr("Feb"), tr("Mar"), tr("Apr"), tr("May"), tr("Jun"), tr("Jul"), tr("Aug"), tr("Sep"), tr("Oct"), tr("Nov"), tr("Dec")};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            FluCalendarItem* label = new FluCalendarItem;
            label->setObjectName("label");
            label->setFixedSize(50, 50);

            label->setText(monthTexts.at((i * 4 + j) % 12));
            label->setAlignment(Qt::AlignCenter);
            label->setProperty("today", false);

            m_labelList.append(label);
            m_gMainLayout->addWidget(label, i, j);

            connect(getItem(i * 4 + j), &FluCalendarItem::clicked, [=]() {
                QDate itemDate = getItem(i * 4 + j)->getCurDate();
                // LOG_DEBUG << itemDate;
                setYearMonth(itemDate.year(), itemDate.month());
                m_parentView->setCurDate(itemDate);
                m_parentView->switchSelectDayView();
                m_parentView->getSelectDayView()->getMonthView()->setYearMonth(itemDate.year(), itemDate.month());
                m_parentView->getSelectMonthView()->setYearMonth(itemDate.year(), itemDate.month());
                m_parentView->getViewTitle()->setYearMonth(itemDate.year(), itemDate.month());
                //   emit m_parentView->selectedDate(itemDate);
                // LOG_DEBUG << "item Clicked!";
            });
        }
    }

    setFixedHeight(300);
    onThemeChanged();
}

void FluCalendarSelectMonthView::setYearMonth(int nYear, int nMonth)
{
    QDate tody = QDate::currentDate();
    if (nYear < 1924 || nYear > 2124)
        return;

    if (nMonth < 0 && nMonth > 12)
        return;

    QDate date(nYear, 1, 1);
    for (int i = 0; i < 16; i++)
    {
        getItem(i)->setInfoText("");
        if (i == 0)
        {
            QString infoText = QString::asprintf("%d", nYear);
            getItem(i)->setInfoText(infoText);
        }

        if (i == 12)
        {
            QString infoText = QString::asprintf("%d", nYear + 1);
            getItem(i)->setInfoText(infoText);
        }

        getItem(i)->setProperty("outRange", false);
        if (i >= 12)
        {
            getItem(i)->setProperty("outRange", true);
        }

        getItem(i)->setCurDate(date);

        getItem(i)->setProperty("today", false);
        if (getItem(i)->getCurDate().year() == QDate::currentDate().year() && getItem(i)->getCurDate().month() == QDate::currentDate().month())
        {
            getItem(i)->setProperty("today", true);
        }

        //  LOG_DEBUG << "date:" << date;
        date = date.addMonths(1);
    }

    updateStyleSheet();
}

void FluCalendarSelectMonthView::updateStyleSheet()
{
    for (int i = 0; i < m_labelList.size(); i++)
    {
        auto label = m_labelList.at(i);
        label->style()->polish(label);
    }
}

QDate FluCalendarSelectMonthView::getPreYear()
{
    return m_parentView->getCurDate().addYears(-1);
}

QDate FluCalendarSelectMonthView::getNextYear()
{
    return m_parentView->getCurDate().addYears(1);
}

void FluCalendarSelectMonthView::gotoPreYear()
{
    QDate date = getPreYear();
    m_parentView->setCurDate(date);
    setYearMonth(date.year(), date.month());
}

void FluCalendarSelectMonthView::gotoNextYear()
{
    QDate date = getNextYear();
    m_parentView->setCurDate(date);
    setYearMonth(date.year(), date.month());
}

FluCalendarItem* FluCalendarSelectMonthView::getItem(int nIndex)
{
    return m_labelList.at(nIndex);
}

void FluCalendarSelectMonthView::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluCalendarSelectMonthView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
