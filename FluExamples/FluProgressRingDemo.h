#pragma once

#include <QWidget>
#include "../FluControls/FluProgressRing.h"
#include <QTimer>

class FluProgressRingDemo : public QWidget
{
  public:
    FluProgressRingDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        auto progressRing1 = new FluProgressRing(this);
        progressRing1->move(50, 50);
        progressRing1->setShowText(true);
        // progressRing->setCurValue(85);

        QTimer* timer = new QTimer(this);
        timer->setInterval(100);
        timer->start();

        m_nTimes = 0;
        connect(timer, &QTimer::timeout, [=]() {
            m_nTimes++;
            m_nTimes = m_nTimes %= 100;
            progressRing1->setCurValue(m_nTimes);
        });

        auto progressRing2 = new FluProgressRing(this);
        progressRing2->move(200, 50);
        progressRing2->setWorking(true);

        resize(600, 400);
    }

  protected:
    int m_nTimes;
};
