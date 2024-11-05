#include "FluDialogsAndFlyoutsPage.h"

FluDialogsAndFlyoutsPage::FluDialogsAndFlyoutsPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_vMainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText("Dialogs & flyouts");

    auto contentDialogCard = new FluHCard(QPixmap("../res/ControlImages/ContentDialog.png"), "ContentDialog", "A dialog box that can be customized to contain any XAML content.");
    contentDialogCard->setKey("ContentDialogPage");
    getFWScrollView()->getMainLayout()->addWidget(contentDialogCard);
    connect(contentDialogCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto flyoutCard = new FluHCard(QPixmap("../res/ControlImages/Flyout.png"), "Flyout", "Shows contextual information and enables user interaction.");
    flyoutCard->setKey("FlyoutPage");
    getFWScrollView()->getMainLayout()->addWidget(flyoutCard);
    connect(flyoutCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto TeachingTipCard = new FluHCard(QPixmap("../res/ControlImages/TeachingTip.png"), "TeachingTip", "A content-rich flyout for guiding users and enabling teaching moments.");
    TeachingTipCard->setKey("TeacingTipPage");
    getFWScrollView()->getMainLayout()->addWidget(TeachingTipCard);
    connect(TeachingTipCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDialogsAndFlyoutsPage.qss", this);
}

void FluDialogsAndFlyoutsPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDialogsAndFlyoutsPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluDialogsAndFlyoutsPage.qss", this);
    }
}
