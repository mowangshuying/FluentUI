#include "FluTabBarDemo.h"

FluTabBarDemo::FluTabBarDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    tabBar = new FluTabBar;
    for (int i = 0; i < 3; i++)
    {
        auto tabBarItem = new FluTabBarItem;
        tabBar->addBarItem(tabBarItem);
    }

    m_vMainLayout = new QVBoxLayout;
    setLayout(m_vMainLayout);

    m_vMainLayout->addWidget(tabBar);
    m_vMainLayout->addStretch(1);

    connect(tabBar, &FluTabBar::addTabBtnClicked, [=]() {
        auto tmpTabBarItem = new FluTabBarItem;
        tabBar->addBarItem(tmpTabBarItem);
    });
    resize(600, 400);
}
