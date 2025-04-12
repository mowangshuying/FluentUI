#include "FluStatusAndInfoPage.h"

FluStatusAndInfoPage::FluStatusAndInfoPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_vMainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText(tr("Status & Info"));

    auto infoBadgeCard = new FluHCard(QPixmap(FLURC("res/ControlImages/InfoBadge.png")), tr("InfoBadge"), tr("An Non-instrusive Ui to display notifications or bring focus to an area."));
    infoBadgeCard->setKey("InfoBadgePage");
    getFWScrollView()->getMainLayout()->addWidget(infoBadgeCard);
    connect(infoBadgeCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto infoBarCard = new FluHCard(QPixmap(FLURC("res/ControlImages/InfoBar.png")), tr("InfoBar"), tr("An inline message to display app-wide status change information."));
    infoBarCard->setKey("InfoBarPage");
    getFWScrollView()->getMainLayout()->addWidget(infoBarCard);
    connect(infoBarCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto progressBarCard = new FluHCard(QPixmap(FLURC("res/ControlImages/ProgressBar.png")), tr("ProgressBar"), tr("Shows the apps progress on a task, or that the app is performing ongoing work that doesn't block user interaction."));
    progressBarCard->setKey("ProgressBarPage");
    getFWScrollView()->getMainLayout()->addWidget(progressBarCard);
    connect(progressBarCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto progressRing = new FluHCard(QPixmap(FLURC("res/ControlImages/ProgressRing.png")), tr("ProgressRing"), tr("Shows the apps progress on a task, or that the app is performing ongoing work that does block user interaction."));
    progressRing->setKey("ProgressRingPage");
    getFWScrollView()->getMainLayout()->addWidget(progressRing);
    connect(progressRing, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto toolTipCard = new FluHCard(QPixmap(FLURC("res/ControlImages/ToolTip.png")), tr("ToolTip"), tr("Displays information for element in a popup window."));
    toolTipCard->setKey("ToolTipPage");
    getFWScrollView()->getMainLayout()->addWidget(toolTipCard);
    connect(toolTipCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluStatusAndInfoPage.qss"), this);
}

void FluStatusAndInfoPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluStatusAndInfoPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluStatusAndInfoPage.qss"), this);
    }
}
