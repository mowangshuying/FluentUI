#pragma once

#include <QWidget>
#include "../FluControls/FluTabBar.h"
#include <QVBoxLayout>
#include "../FluControls/FluTabBarItem.h"

class FluTabBarDemo : public QWidget
{
    Q_OBJECT
  public:
      FluTabBarDemo(QWidget* parent = nullptr) : QWidget(parent)
      {
          auto tabBar = new FluTabBar;
          auto tabBarItem1 = new FluTabBarItem;
          auto tabBarItem2 = new FluTabBarItem;


          tabBar->addBarItem(tabBarItem1);
          tabBar->addBarItem(tabBarItem2);


          m_vMainLayout = new QVBoxLayout;
          setLayout(m_vMainLayout);

          m_vMainLayout->addWidget(tabBar);
          m_vMainLayout->addStretch(1);

          resize(600, 400);
      }

  protected:
      QVBoxLayout* m_vMainLayout;
};
