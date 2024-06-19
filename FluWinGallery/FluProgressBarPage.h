#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluProgressBar.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluProgressBarPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluProgressBarPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("ProgressBarPage");
        m_infoLabel->setText(
            "The ProgressBar has two different visual representations.\nIndeterminate - shows that a task is ongoing, but doesn't block user interaction.\nDeterminate - show how much progress has been made on a kknown amount of work.");

        auto displayBox1 = new FluDisplayBox;
        displayBox1->setTitle("An indeterminate progress ring.");
        displayBox1->getCodeExpander()->setCodeByPath("../code/ProgressBarPageCode1.md");
        displayBox1->setBodyWidgetFixedHeight(96);

        auto progressBar1 = new FluProgressBar(displayBox1);
        progressBar1->move(50, 70);
        progressBar1->setValue(75);
        progressBar1->setFixedWidth(150);

        // progressRing1->setWorking(true);

        m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluProgressBarPage.qss", this);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluProgressBarPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluProgressBarPage.qss", this);
        }
    }
};
