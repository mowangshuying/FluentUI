#pragma once

#include "../controls/FluWidget.h"
#include "../controls/FluTabBarContent.h"
#include <QVBoxLayout>
#include "../controls/FluTabBarItem.h"
#include "../controls/FluTabBar.h"
#include "../examples/FluTemplateDemo.h"

class FluTabBarDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluTabBarDemo(QWidget* parent = nullptr);

  protected:
    FluTabBar* tabBar;
    QVBoxLayout* m_mainLayout;
};
