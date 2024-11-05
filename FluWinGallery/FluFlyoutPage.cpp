#include "FluFlyoutPage.h"

FluFlyoutPage::FluFlyoutPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("Flyout");
    m_infoLabel->setText(
        "A Flyout displays lightweight UI that is either information, or requires user interaction. Unlike a dialog, a Flyout can be light dismissed by clicking or tapping off of it.Use it to collect input from the user, show more details "
        "about an item, or ask the user to confirm an action.");

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle("A button with a flyout.");
    displayBox->getCodeExpander()->setCodeByPath("../code/FlyoutPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(96);

    auto emptyCartBtn = new FluPushButton;
    emptyCartBtn->setFixedWidth(96);
    emptyCartBtn->setText("Empty cart");

    connect(emptyCartBtn, &FluPushButton::clicked, this, [=]() {
        auto flyout = new FluConfirmFlyout(emptyCartBtn, FluFlyoutPosition::Top);
        flyout->setTitle("Empty your cart?");
        flyout->setInfo("All item will be remove. Do your want to continue?");
        flyout->show();
    });

    displayBox->getBodyLayout()->addWidget(emptyCartBtn);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluFlyoutPage.qss", this);
}

void FluFlyoutPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluFlyoutPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluFlyoutPage.qss", this);
    }
}
