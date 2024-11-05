#include "FluMenuAndToolBarsPage.h"

FluMenuAndToolBarsPage::FluMenuAndToolBarsPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_vMainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("Menus & toolbars");

    auto appBarButtonCard = new FluHCard(QPixmap("../res/ControlImages/AppBarButton.png"), "AppBarButton", "A button that's styled for use in a CommandBar.");
    appBarButtonCard->setKey("AppBarButtonPage");
    getFWScrollView()->getMainLayout()->addWidget(appBarButtonCard);
    connect(appBarButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto appBarSeparatorCard = new FluHCard(QPixmap("../res/ControlImages/AppBarSeparator.png"), "AppBarSeparator", "A vertical line that's used to visually separate groups of commands in an app bar.");
    appBarSeparatorCard->setKey("AppBarSeparatorPage");
    getFWScrollView()->getMainLayout()->addWidget(appBarSeparatorCard);
    connect(appBarSeparatorCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto appBarToggleButtonCard =
        new FluHCard(QPixmap("../res/ControlImages/AppBarToggleButton.png"), "AppBarToggleButton", "A button that can be on, off, or indeterminate like a CheckBox, and is styled for use in an app bar or other specialized UI.");
    appBarToggleButtonCard->setKey("AppBarToggleButtonPage");
    getFWScrollView()->getMainLayout()->addWidget(appBarToggleButtonCard);
    connect(appBarToggleButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto commandBarCard = new FluHCard(QPixmap("../res/ControlImages/CommandBar.png"), "CommandBar", "A toolbar for displaying application-specific commands that hanles layout and resizing of its contents.");
    commandBarCard->setKey("CommandBarPage");
    getFWScrollView()->getMainLayout()->addWidget(commandBarCard);
    connect(commandBarCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto commandBarFlyoutCard = new FluHCard(QPixmap("../res/ControlImages/CommandBarFlyout.png"), "CommandBarFlyout", "A mini-toolbar displaying proactive commands, and an optional menu of command.");
    commandBarFlyoutCard->setKey("CommandBarFlyoutPage");
    getFWScrollView()->getMainLayout()->addWidget(commandBarFlyoutCard);
    connect(commandBarFlyoutCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto menuBarCard = new FluHCard(QPixmap("../res/ControlImages/MenuBar.png"), "MenuBar", "A classic menu, allowing the display of MenuItems containing MenuFlyoutItems.");
    menuBarCard->setKey("MenuBarPage");
    getFWScrollView()->getMainLayout()->addWidget(menuBarCard);
    connect(menuBarCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto menuFlyoutCard = new FluHCard(QPixmap("../res/ControlImages/MenuFlyout.png"), "MenuFlyout", "Shows a contextual list of simple command or options.");
    menuFlyoutCard->setKey("MenuFlyoutPage");
    getFWScrollView()->getMainLayout()->addWidget(menuFlyoutCard);
    connect(menuFlyoutCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto standUICommandCard = new FluHCard(QPixmap("../res/ControlImages/StandardUICommand.png"), "StandardUICommand", "A StandardUICommand is a built-in 'XamlUICommand' which represents a commonly used command, e.g.'save'.");
    standUICommandCard->setKey("StandardUICommandPage");
    getFWScrollView()->getMainLayout()->addWidget(standUICommandCard);
    connect(standUICommandCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto swipeControlCard = new FluHCard(QPixmap("../res/ControlImages/SwipeControl.png"), "SwipeControl", "Touch gesture for quick menu actions on items.");
    swipeControlCard->setKey("SwipeControlPage");
    getFWScrollView()->getMainLayout()->addWidget(swipeControlCard);
    connect(swipeControlCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });
}

void FluMenuAndToolBarsPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMenuAndToolBarsPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluMenuAndToolBarsPage.qss", this);
    }
}
