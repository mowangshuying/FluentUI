#pragma once

#include "FluAEmptyPage.h"
#include "FluATitlePage.h"
#include "../FluControls/FluHCard.h"
#include "../FluControls/FluFWScrollView.h"

#include "../FluUtils/FluUtils.h"

class FluNavigationPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluNavigationPage(QWidget* parent = nullptr) : FluATitlePage(parent)
    {
        m_vMainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("Navigation");

        auto breadcrumbBarCard = new FluHCard(QPixmap("../res/ControlImages/BreadcrumbBar.png"), "BreadcrumbBar", "Shows the trail of navigation taken to the current location..");
        breadcrumbBarCard->setKey("BreadcrumbBarPage");
        getFWScrollView()->getMainLayout()->addWidget(breadcrumbBarCard);
        connect(breadcrumbBarCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        auto navigationViewCard = new FluHCard(QPixmap("../res/ControlImages/NavigationView.png"), "NavigationView", "Common vertical layout for top-level areas of your app via a collapsible navigation menu.");
        navigationViewCard->setKey("NavigationViewPage");
        getFWScrollView()->getMainLayout()->addWidget(navigationViewCard);
        connect(navigationViewCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        auto pivotCard = new FluHCard(QPixmap("../res/ControlImages/Pivot.png"), "Pivot", "Presents information from different sources in a tabbed view..");
        pivotCard->setKey("PivotPage");
        getFWScrollView()->getMainLayout()->addWidget(pivotCard);
        connect(pivotCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        auto selectorBarCard = new FluHCard(QPixmap("../res/ControlImages/Pivot.png"), "SelectorBar", "Presents information from a small set of different sources. The user can pick one of them.");
        selectorBarCard->setKey("SelectorBarPage");
        getFWScrollView()->getMainLayout()->addWidget(selectorBarCard);
        connect(selectorBarCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

        auto tabViewCard = new FluHCard(QPixmap("../res/ControlImages/TabView.png"), "TabView", "A control that displays a collection of tabs that can be used to display several documents.");
        tabViewCard->setKey("TabViewPage");
        getFWScrollView()->getMainLayout()->addWidget(tabViewCard);
        connect(tabViewCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });
    }

  signals:
    void clickedHCard(QString key);
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNavigationPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluNavigationPage.qss", this);
        }
    }
};
