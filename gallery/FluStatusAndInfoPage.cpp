#include "FluStatusAndInfoPage.h"

FluStatusAndInfoPage::FluStatusAndInfoPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_mainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText(tr("Status & Info"));

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/InfoBadge.png")), tr("InfoBadge"), tr("An Non-instrusive Ui to display notifications or bring focus to an area."), "InfoBadgePage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/InfoBar.png")), tr("InfoBar"), tr("An inline message to display app-wide status change information."), "InfoBarPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ProgressBar.png")), tr("ProgressBar"), tr("Shows the apps progress on a task, or that the app is performing ongoing work that doesn't block user interaction."), "ProgressBarPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ProgressRing.png")), tr("ProgressRing"), tr("Shows the apps progress on a task, or that the app is performing ongoing work that does block user interaction."), "ProgressRingPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ToolTip.png")), tr("ToolTip"), tr("Displays information for element in a popup window."), "ToolTipPage");

    onThemeChanged();
}

void FluStatusAndInfoPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluStatusAndInfoPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
