#include "FluMenuAndToolBarsPage.h"

FluMenuAndToolBarsPage::FluMenuAndToolBarsPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("Menus & toolbars"));

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/AppBarButton.png")), tr("AppBarButton"), tr("A button that's styled for use in a CommandBar."), "AppBarButtonPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/AppBarSeparator.png")), tr("AppBarSeparator"), tr("A vertical line that's used to visually separate groups of commands in an app bar."), "AppBarSeparatorPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/AppBarToggleButton.png")),
             tr("AppBarToggleButton"),
             tr("A button that can be on, off, or indeterminate like a CheckBox, and is styled for use in an app bar or other specialized UI."),
             "AppBarToggleButtonPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/CommandBar.png")), tr("CommandBar"), tr("A toolbar for displaying application-specific commands that hanles layout and resizing of its contents."), "CommandBarPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/CommandBarFlyout.png")), tr("CommandBarFlyout"), tr("A mini-toolbar displaying proactive commands, and an optional menu of command."), "CommandBarFlyoutPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/MenuBar.png")), tr("MenuBar"), tr("A classic menu, allowing the display of MenuItems containing MenuFlyoutItems."), "MenuBarPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/MenuFlyout.png")), tr("MenuFlyout"), tr("Shows a contextual list of simple command or options."), "MenuFlyoutPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/StandardUICommand.png")),
             tr("StandardUICommand"),
             tr("A StandardUICommand is a built-in 'XamlUICommand' which represents a commonly used command, e.g.'save'."),
             tr("StandardUICommandPage"));

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/SwipeControl.png")), tr("SwipeControl"), tr("Touch gesture for quick menu actions on items."), tr("SwipeControlPage"));

    onThemeChanged();
}

void FluMenuAndToolBarsPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluMenuAndToolBarsPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
