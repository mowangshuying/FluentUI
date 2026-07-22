#include "FluTabBarDemo.h"

FluTabBarDemo::FluTabBarDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    tabBar = new FluTabBar;
    for (int i = 0; i < 3; i++)
    {
        auto tabBarItem = new FluTabBarItem;
        tabBar->addBarItem(tabBarItem);
    }

    // m_mainLayout = new QVBoxLayout;
    // setLayout(m_mainLayout);

    // m_mainLayout->addWidget(tabBar);
    // m_mainLayout->addStretch(1);

    connect(tabBar, &FluTabBar::addTabBtnClicked, [=]() {
        auto tmpTabBarItem = new FluTabBarItem;
        QString text = QString::asprintf("Document %d ----------------", tabBar->getTabBarItems().size() + 1);
        tmpTabBarItem->setText(text);
        tabBar->addBarItem(tmpTabBarItem);
    });

    // m_contentLayout->addWidget(tabBar);

    auto vLayout = new QVBoxLayout;
    vLayout->addWidget(tabBar);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->addStretch();

    m_contentLayout->addLayout(vLayout);
    resize(600, 400);
}
