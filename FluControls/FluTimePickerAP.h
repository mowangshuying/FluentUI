#pragma once

#include "../FluUtils/FluUtils.h"
#include <QPushButton>
#include "FluWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QStyleOption>
#include <QPainter>

#include "FluTimePickerAPView.h"

class FluTimePickerAP : public FluWidget
{
    Q_OBJECT
  public:
    FluTimePickerAP(QWidget* parent = nullptr) : FluWidget(parent)
    {
        m_hMainLayout = new QHBoxLayout;
        m_hMainLayout->setContentsMargins(0, 0, 0, 0);
        m_hMainLayout->setSpacing(0);
        setLayout(m_hMainLayout);

        m_hourBtn = new QPushButton;
        m_hourBtn->setText("hour");
        m_hourBtn->setObjectName("hourBtn");

        m_minuteBtn = new QPushButton;
        m_minuteBtn->setText("minute");
        m_minuteBtn->setObjectName("minuteBtn");

        m_apBtn = new QPushButton;
        m_apBtn->setText("AM");
        m_apBtn->setObjectName("apBtn");

        m_hourBtn->setFixedHeight(30);
        m_minuteBtn->setFixedHeight(30);
        m_apBtn->setFixedHeight(30);

        m_hMainLayout->addWidget(m_hourBtn);
        m_hMainLayout->addWidget(m_minuteBtn);
        m_hMainLayout->addWidget(m_apBtn);

        m_timerPickerApView = new FluTimePickerAPView;
        m_timerPickerApView->setFixedWidth(240);
        m_timerPickerApView->hide();

        setFixedSize(240, 30);
        connect(m_hourBtn, &QPushButton::clicked, [=]() { emit clicked(); });
        connect(m_minuteBtn, &QPushButton::clicked, [=]() { emit clicked(); });
        connect(this, &FluTimePickerAP::clicked, [=]() {
            // get current time
            LOG_DEBUG << "Called";
            // show FluTimerPickerView

            int nX = 0;
            int nY = height() / 2 - 180;
            QPoint gPoint = mapToGlobal(QPoint(nX, nY));
            m_timerPickerApView->move(gPoint.x(), gPoint.y());
            m_timerPickerApView->show();
        });

        connect(m_timerPickerApView, &FluTimePickerAPView::clickedOk, [=]() {
            QString sHour = QString::asprintf("%02d", m_timerPickerApView->getHour());
            m_hourBtn->setText(sHour);

            QString sMinute = QString::asprintf("%02d", m_timerPickerApView->getMinute());
            m_minuteBtn->setText(sMinute);

            QString sAmOrPm = m_timerPickerApView->isAm() ? "AM" : "PM";
            m_apBtn->setText(sAmOrPm);
        });

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTimePickerAP.qss", this);
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
        emit clicked();
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
  signals:
    void clicked();
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTimePickerAP.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTimePickerAP.qss", this);
        }
    }

  protected:
    QHBoxLayout* m_hMainLayout;
    QPushButton* m_hourBtn;
    QPushButton* m_minuteBtn;
    QPushButton* m_apBtn;

    FluTimePickerAPView* m_timerPickerApView;
};
