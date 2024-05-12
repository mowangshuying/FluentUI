#pragma once

#include "FluWidget.h"
#include "FluLoopView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QPushButton>
#include <QPainter>
#include <QStyleOption>
#include "FluAmPmView.h"
#include "FluHSplitLine.h"
#include "FluVSplitLine.h"

class FluTimePickerAPView : public FluWidget
{
    Q_OBJECT
  public:
    FluTimePickerAPView(QWidget* parent = nullptr) : FluWidget(parent), m_bAm(true), m_hour(0), m_minute(0), m_bFirstShow(true)
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

        m_hourView = new FluLoopView(80);
        m_minuteView = new FluLoopView(80);
        m_ampmView = new FluAmPmView(80);

        // set hour data;
        std::vector<QString> datas;
        for (int i = 0; i < 12; i++)
        {
            QString str = QString::asprintf("%02d", i);
            datas.push_back(str);
        }
        m_hourView->setAllItems(datas);

        // set minute data;
        datas.clear();
        for (int i = 0; i < 60; i++)
        {
            QString str = QString::asprintf("%02d", i);
            datas.push_back(str);
        }
        m_minuteView->setAllItems(datas);

        m_hViewLayout->setSpacing(0);
        m_hViewLayout->addWidget(m_hourView);
        m_hViewLayout->addWidget(new FluHSplitLine);
        m_hViewLayout->addWidget(m_minuteView);
        m_hViewLayout->addWidget(new FluHSplitLine);
        m_hViewLayout->addWidget(m_ampmView);

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

        setMinute(0);
        setHour(0);

        connect(m_okBtn, &QPushButton::clicked, [=]() {
            updateTime();
            emit clickedOk();
            close();
        });
        connect(m_cancelBtn, &QPushButton::clicked, [=]() {
            emit clickedCancel();
            close();
        });

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTimePickerAPView.qss", this);
        // connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); }); { onThemeChanged(); });
    }

    int getHour()
    {
        return m_hour;
    }

    int getMinute()
    {
        return m_minute;
    }

    void setHour(int hour)
    {
        m_hour = hour;
        m_hourView->setVisibaleMidIndex(hour);
        // m_hourView->scrollTo(hour);
    }

    void setMinute(int minute)
    {
        m_minute = minute;
        m_minuteView->setVisibaleMidIndex(minute);
        // m_hourView->scrollTo(minute);
    }

    bool isAm()
    {
        return m_bAm;
    }

    void setAm(bool bAm)
    {
        m_bAm = bAm;
    }

    void updateTime()
    {
        m_hour = m_hourView->getVisibleMidIndex();
        m_minute = m_minuteView->getVisibleMidIndex();
        m_bAm = m_ampmView->isAm();
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
        if (m_bFirstShow)
        {
            m_bFirstShow = false;
            m_hourView->scrollTo(m_hour);
            m_minuteView->scrollTo(m_minute);
        }
    }
  signals:
    void clickedOk();
    void clickedCancel();
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            m_okBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept, FluTheme::Light));
            m_cancelBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel, FluTheme::Light));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTimePickerAPView.qss", this);
        }
        else
        {
            m_okBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept, FluTheme::Dark));
            m_cancelBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel, FluTheme::Dark));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTimePickerAPView.qss", this);
        }
    }

  protected:
    QVBoxLayout* m_vMainLayout;
    QHBoxLayout* m_hViewLayout;
    QHBoxLayout* m_hBtnLayout;

    FluLoopView* m_hourView;
    FluLoopView* m_minuteView;
    FluAmPmView* m_ampmView;

    QPushButton* m_okBtn;
    QPushButton* m_cancelBtn;

    int m_hour;
    int m_minute;
    bool m_bAm;

    bool m_bFirstShow;
};
