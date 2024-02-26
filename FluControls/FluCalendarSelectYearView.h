#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "../FluUtils/FluUtils.h"
#include "FluCalendarItem.h"

class FluCalendarSelectYearView : public QWidget
{
  public:
    FluCalendarSelectYearView(QWidget* parent = nullptr) : QWidget(parent)
    {
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

                label->setText(QString::asprintf("%d", i * 4 + j + 1));
                label->setAlignment(Qt::AlignCenter);
                label->setProperty("today", false);

                m_labelList.append(label);
                m_gMainLayout->addWidget(label, i, j);
            }
        }

        // 1930 - 1939
        // 1940 - 1949
        // 1950 - 1959
        // 1960 - 1969
        // 1970 - 1979
        // 1980 - 1989
        // 1990 - 1999

        // 2000 - 2009
        // 2010 - 2019
        // 2020 - 2029
        // 2030 - 2039
        // 2040 - 2049
        // 2050 - 2059
        // 2060 - 2069
        // 2070 - 2079
        // 2080 - 2089
        // 2090 - 2099
        
        // 2100 - 2109

        setFixedHeight(300);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarSelectYearView.qss", this);
    }

    FluCalendarItem* getItem(int nIndex)
    {
        if (nIndex < 0 || nIndex >= m_labelList.size())
            return nullptr;

        return m_labelList.at(nIndex);
    }

  protected:
    QGridLayout* m_gMainLayout;
    QList<FluCalendarItem*> m_labelList;
    QDate m_curYear;
};
