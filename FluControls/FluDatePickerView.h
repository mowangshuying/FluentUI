#pragma once

#include <QWidget>
#include "FluLoopView.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "../FluUtils/FluUtils.h"
#include <QPainter>
#include <QStyleOption>
#include "FluHSplitLine.h"
#include "FluVSplitLine.h"

class FluDatePickerView : public QWidget
{
    Q_OBJECT
  public:
    FluDatePickerView(QWidget* parent = nullptr) : QWidget(parent), m_bFirstShow(true)
    {
        setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);

        m_vMainLayout = new QVBoxLayout;
        m_vMainLayout->setContentsMargins(0, 0, 0, 0);
        m_vMainLayout->setSpacing(0);
        setLayout(m_vMainLayout);

        m_hViewLayout = new QHBoxLayout;
        // setLayout(m_hViewLayout);
        m_vMainLayout->addLayout(m_hViewLayout);

        m_monthView = new FluLoopView(140);
        m_dayView = new FluLoopView(80);
        m_yearView = new FluLoopView(80);

        // set month data;
        std::vector<QString> datas{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        m_monthView->setAllItems(datas);

        // set day data;
        datas.clear();
        for (int i = 0; i < 30; i++)
        {
            QString str = QString::asprintf("%02d", i + 1);
            datas.push_back(str);
        }
        m_dayView->setAllItems(datas);

        datas.clear();
        for (int i = 0; i < 200; i++)
        {
            QString str = QString::asprintf("%04d", i + 1924);
            datas.push_back(str);
        }
        m_yearView->setAllItems(datas);

        m_hViewLayout->setSpacing(0);
        m_hViewLayout->addWidget(m_monthView);
        m_hViewLayout->addWidget(new FluHSplitLine);
        m_hViewLayout->addWidget(m_dayView);
        m_hViewLayout->addWidget(new FluHSplitLine);
        m_hViewLayout->addWidget(m_yearView);

        m_hBtnLayout = new QHBoxLayout;
        m_hBtnLayout->setContentsMargins(5, 5, 5, 5);

        m_okBtn = new QPushButton;
        m_cancelBtn = new QPushButton;

        m_okBtn->setObjectName("okBtn");
        m_cancelBtn->setObjectName("cancelBtn");

        m_okBtn->setFixedHeight(40);
        m_cancelBtn->setFixedHeight(40);

        m_okBtn->setIconSize(QSize(25, 25));
        m_okBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept));

        m_cancelBtn->setIconSize(QSize(25, 25));
        m_cancelBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel));

        m_hBtnLayout->addWidget(m_okBtn);
        m_hBtnLayout->addWidget(m_cancelBtn);

        m_vMainLayout->addWidget(new FluVSplitLine);
        m_vMainLayout->addLayout(m_hBtnLayout);

        setDay(0);
        setMonth(0);
        setYear(0 + 100);

        connect(m_okBtn, &QPushButton::clicked, [=]() {
            updateTime();
            emit clickedOk();
            close();
        });
        connect(m_cancelBtn, &QPushButton::clicked, [=]() {
            emit clickedCancel();
            close();
        });

        connect(m_monthView, &FluLoopView::visibaleMidIndexChanged, [=](int nIndex) {
            int nDays = getMonthDays(m_yearView->getVisibleMidIndex() + 1924, m_monthView->getVisibleMidIndex() + 1);
            std::vector<QString> datas;
            for (int i = 0; i < nDays; i++)
            {
                QString str = QString::asprintf("%02d", i + 1);
                datas.push_back(str);
            }

            m_dayView->clear();
            m_dayView->setAllItems(datas);
            m_dayView->setVisibaleMidIndex(m_dayView->getVisibleMidIndex());
        });

        connect(m_yearView, &FluLoopView::visibaleMidIndexChanged, [=](int nIndex) {
            int nDays = getMonthDays(m_yearView->getVisibleMidIndex() + 1924, m_monthView->getVisibleMidIndex() + 1);
            std::vector<QString> datas;
            for (int i = 0; i < nDays; i++)
            {
                QString str = QString::asprintf("%02d", i + 1);
                datas.push_back(str);
            }

            m_dayView->clear();
            m_dayView->setAllItems(datas);
            m_dayView->setVisibaleMidIndex(m_dayView->getVisibleMidIndex());
        });

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDatePickerView.qss", this);
    }

    int getMonth()
    {
        return m_month;
    }

    int getDay()
    {
        return m_day;
    }

    int getYear()
    {
        return m_year;
    }

    void setMonth(int month)
    {
        m_month = month;
        m_monthView->setVisibaleMidIndex(month);
        // m_hourView->scrollTo(hour);
    }

    void setDay(int day)
    {
        m_day = day;
        m_dayView->setVisibaleMidIndex(day);
        // m_hourView->scrollTo(minute);
    }

    void setYear(int year)
    {
        m_year = year;
        m_yearView->setVisibaleMidIndex(year);
    }

    void updateTime()
    {
        m_month = m_monthView->getVisibleMidIndex();
        m_day = m_dayView->getVisibleMidIndex();
        m_year = m_yearView->getVisibleMidIndex();
    }

    int getMonthDays(int year, int month)
    {
        // get Month, getYear, output days;
        QDate date(year, month, 1);
        int count = 0;
        while (1)
        {
            count++;
            date = date.addDays(1);
            if (month != date.month())
            {
                break;
            }
        }
        return count;
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

    void showEvent(QShowEvent* event)
    {
        if (!m_bFirstShow)
            return;

        m_bFirstShow = false;
        m_monthView->scrollTo(m_month);
        m_dayView->scrollTo(m_day);
        m_yearView->scrollTo(m_year);
    }
  signals:
    void clickedOk();
    void clickedCancel();

  protected:
    QVBoxLayout* m_vMainLayout;
    QHBoxLayout* m_hViewLayout;
    QHBoxLayout* m_hBtnLayout;

    FluLoopView* m_monthView;
    FluLoopView* m_dayView;
    FluLoopView* m_yearView;

    QPushButton* m_okBtn;
    QPushButton* m_cancelBtn;

    int m_month;
    int m_day;
    int m_year;

    bool m_bFirstShow;
};
