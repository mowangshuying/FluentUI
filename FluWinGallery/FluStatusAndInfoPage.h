#pragma once

#include "FluAEmptyPage.h"
#include "FluATitlePage.h"
#include "../FluControls/FluHCard.h"
#include "../FluControls/FluFWScrollView.h"

class FluStatusAndInfoPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluStatusAndInfoPage(QWidget* parent = nullptr) : FluATitlePage(parent)
    {
        m_vMainLayout->setContentsMargins(35, 35, 0, 35);
        m_titleLabel->setText("Status & Info");

        auto infoBadgeCard = new FluHCard(QPixmap("../res/ControlImages/InfoBadge.png"), "InfoBadge", "An Non-instrusive Ui to display notifications or bring focus to an area.");
        infoBadgeCard->setKey("InfoBadgePage");
        getFWScrollView()->getMainLayout()->addWidget(infoBadgeCard);
        connect(infoBadgeCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        auto infoBarCard = new FluHCard(QPixmap("../res/ControlImages/InfoBar.png"), "InfoBar", "An inline message to display app-wide status change information.");
        infoBarCard->setKey("InfoBarPage");
        getFWScrollView()->getMainLayout()->addWidget(infoBarCard);
        connect(infoBarCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        auto progressBarCard = new FluHCard(QPixmap("../res/ControlImages/ProgressBar.png"), "ProgressBar", "Shows the apps progress on a task, or that the app is performing ongoing work that doesn't block user interaction.");
        progressBarCard->setKey("ProgressBarPage");
        getFWScrollView()->getMainLayout()->addWidget(progressBarCard);
        connect(progressBarCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        auto progressRing = new FluHCard(QPixmap("../res/ControlImages/ProgressRing.png"), "ProgressRing", "Shows the apps progress on a task, or that the app is performing ongoing work that does block user interaction.");
        progressRing->setKey("ProgressRingPage");
        getFWScrollView()->getMainLayout()->addWidget(progressRing);
        connect(progressRing, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        auto toolTipCard = new FluHCard(QPixmap("../res/ControlImages/ToolTip.png"), "ToolTip", "Displays information for element in a popup window.");
        toolTipCard->setKey("ToolTipPage");
        getFWScrollView()->getMainLayout()->addWidget(toolTipCard);
        connect(toolTipCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluStatusAndInfoPage.qss", this);
        
    }
  signals:
    void clickedHCard(QString key);
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluStatusAndInfoPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluStatusAndInfoPage.qss", this);
        }
    }
};
