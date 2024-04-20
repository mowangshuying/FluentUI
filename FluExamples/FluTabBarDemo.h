#pragma once

#include <QWidget>
#include "../FluControls/FluTabBarContent.h"
#include <QVBoxLayout>
#include "../FluControls/FluTabBarItem.h"
#include "../FluControls/FluTabBar.h"

class FluTabBarDemo : public QWidget
{
    Q_OBJECT
  public:
    FluTabBarDemo(QWidget* parent = nullptr) : QWidget(parent)
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

        resize(600, 400);
    }

    // void resizeEvent(QResizeEvent* event)
    //{
    //       tabBar->setFixedWidth(width());
    // }

  protected:
    FluTabBar* tabBar;
    QVBoxLayout* m_vMainLayout;
};
