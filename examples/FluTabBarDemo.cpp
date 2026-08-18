#include "FluTabBarDemo.h"

FluTabBarDemo::FluTabBarDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    auto vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 0, 0);

    tabBar = new FluTabBar;
    vLayout->addWidget(tabBar);
    vLayout->addStretch();
    m_contentLayout->addLayout(vLayout);

    for (int i = 0; i < 3; i++)
    {
        auto tabBarItem = new FluTabBarItem;
        tabBar->addBarItem(tabBarItem);
    }

    connect(tabBar, &FluTabBar::addTabButtonClicked, [=]() {
        auto tmpTabBarItem = new FluTabBarItem;
        QString text = QString::asprintf("Document %d ----------------", tabBar->getTabBarItems().size() + 1);
        tmpTabBarItem->setText(text);
        tabBar->addBarItem(tmpTabBarItem);
    });

    // m_contentLayout->addWidget(tabBar);

    //auto vLayout = new QVBoxLayout;
    //vLayout->addWidget(tabBar);
    //vLayout->setContentsMargins(0, 0, 0, 0);
    //vLayout->addStretch();

    //m_contentLayout->addLayout(vLayout);
    resize(600, 400);
}
