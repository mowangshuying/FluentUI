#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "../FluUtils/FluUtils.h"
#include "FluCalendarItem.h"

class FluCalendarSelectMonthView : public QWidget
{
  public:
    FluCalendarSelectMonthView(QWidget* parent = nullptr) : QWidget(parent)
    {
        m_gMainLayout = new QGridLayout;
        m_gMainLayout->setContentsMargins(10, 0, 10, 0);
        m_gMainLayout->setSpacing(0);
        m_gMainLayout->setVerticalSpacing(5);
        setLayout(m_gMainLayout);

        QList<QString> monthTexts = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
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
            }
        }

        setFixedHeight(300);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarSelectMonthView.qss", this);
    }

    void setYearMonth(int nYear, int nMonth)
    {
    }

  protected:
    QGridLayout* m_gMainLayout;
    QList<QLabel*> m_labelList;
    // QDate m_curYear;
};
