#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluProgressRing.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluProgressRingPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluProgressRingPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("ProgressRingPage");
        // m_subTitleLabel->setText("CppQtFluentUi888::FluProgressRing");

        m_infoLabel->setText("The ProgressRing has two different visual representations.\nIndeterminate - shows that a task is ongoing.but blocks user interaction.\nDeterminate - shows how much progress has been made on a known amount of work.");

        auto displayBox1 = new FluDisplayBox;
        displayBox1->setTitle("An indeterminate progress ring.");
        displayBox1->getCodeExpander()->setCodeByPath("../code/ProgressRingPageCode1.md");
        displayBox1->setBodyWidgetFixedHeight(96);

        auto progressRing1 = new FluProgressRing(displayBox1);
        progressRing1->move(50, 50);
        progressRing1->setWorking(true);

        m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

        auto displayBox2 = new FluDisplayBox;
        displayBox2->setTitle("An indeterminate ring.");
        displayBox2->getCodeExpander()->setCodeByPath("../code/ProgressRingPageCode2.md");
        displayBox2->setBodyWidgetFixedHeight(96);

        auto progressRing2 = new FluProgressRing(displayBox2);
        progressRing2->move(50, 50);
        progressRing2->setShowText(true);
        // progressRing->setCurValue(85);

        QTimer* timer = new QTimer(this);
        timer->setInterval(100);
        timer->start();

        m_nTimes = 0;
        connect(timer, &QTimer::timeout, [=]() {
            m_nTimes++;
            m_nTimes = m_nTimes %= 100;
            progressRing2->setCurValue(m_nTimes);
        });

        // displayBox1->getBodyLayout()->addWidget(checkBox);
        m_vScrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluProgressRingPage.qss", this);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluProgressRingPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluProgressRingPage.qss", this);
        }
    }

  protected:
    int m_nTimes;
};
