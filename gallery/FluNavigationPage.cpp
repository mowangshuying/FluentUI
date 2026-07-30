#include "FluNavigationPage.h"

FluNavigationPage::FluNavigationPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("Navigation"));

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/BreadcrumbBar.png")), tr("BreadcrumbBar"), tr("Shows the trail of navigation taken to the current location.."), "BreadcrumbBarPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/NavigationView.png")), tr("NavigationView"), tr("Common vertical layout for top-level areas of your app via a collapsible navigation menu."), "NavigationViewPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Pivot.png")), tr("Pivot"), tr("Presents information from different sources in a tabbed view.."), "PivotPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Pivot.png")), tr("SelectorBar"), tr("Presents information from a small set of different sources. The user can pick one of them."), "SelectorBarPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/TabView.png")), tr("TabView"), tr("A control that displays a collection of tabs that can be used to display several documents."), "TabViewPage");

    onThemeChanged();
}

void FluNavigationPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluNavigationPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
