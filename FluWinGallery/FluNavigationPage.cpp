#include "FluNavigationPage.h"

FluNavigationPage::FluNavigationPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_vMainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("Navigation"));

    auto breadcrumbBarCard = new FluHCard(FluIconUtils::getPixmap(("../res/ControlImages/BreadcrumbBar.png")), tr("BreadcrumbBar"), tr("Shows the trail of navigation taken to the current location.."));
    breadcrumbBarCard->setKey("BreadcrumbBarPage");
    getFWScrollView()->getMainLayout()->addWidget(breadcrumbBarCard);
    connect(breadcrumbBarCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto navigationViewCard = new FluHCard(FluIconUtils::getPixmap(("../res/ControlImages/NavigationView.png")), tr("NavigationView"), tr("Common vertical layout for top-level areas of your app via a collapsible navigation menu."));
    navigationViewCard->setKey("NavigationViewPage");
    getFWScrollView()->getMainLayout()->addWidget(navigationViewCard);
    connect(navigationViewCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto pivotCard = new FluHCard(FluIconUtils::getPixmap(("../res/ControlImages/Pivot.png")), tr("Pivot"), tr("Presents information from different sources in a tabbed view.."));
    pivotCard->setKey("PivotPage");
    getFWScrollView()->getMainLayout()->addWidget(pivotCard);
    connect(pivotCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto selectorBarCard = new FluHCard(FluIconUtils::getPixmap(("../res/ControlImages/Pivot.png")), tr("SelectorBar"), tr("Presents information from a small set of different sources. The user can pick one of them."));
    selectorBarCard->setKey("SelectorBarPage");
    getFWScrollView()->getMainLayout()->addWidget(selectorBarCard);
    connect(selectorBarCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto tabViewCard = new FluHCard(FluIconUtils::getPixmap(("../res/ControlImages/TabView.png")), tr("TabView"), tr("A control that displays a collection of tabs that can be used to display several documents."));
    tabViewCard->setKey("TabViewPage");
    getFWScrollView()->getMainLayout()->addWidget(tabViewCard);
    connect(tabViewCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    onThemeChanged();
}

void FluNavigationPage::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluNavigationPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
