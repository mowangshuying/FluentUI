#include "FluDialogsAndFlyoutsPage.h"

FluDialogsAndFlyoutsPage::FluDialogsAndFlyoutsPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_mainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText(tr("Dialogs & flyouts"));

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ContentDialog.png")), tr("ContentDialog"), tr("A dialog box that can be customized to contain any XAML content."), "ContentDialogPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Flyout.png")), tr("Flyout"), tr("Shows contextual information and enables user interaction."), "FlyoutPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/TeachingTip.png")), tr("TeachingTip"), tr("A content-rich flyout for guiding users and enabling teaching moments."), "TeacingTipPage");
    onThemeChanged();
}

void FluDialogsAndFlyoutsPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluDialogsAndFlyoutsPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
