#pragma once

#include "../Controls/FluWidget.h"
#include "../Controls/FluTabBarContent.h"
#include <QVBoxLayout>
#include "../Controls/FluTabBarItem.h"
#include "../Controls/FluTabBar.h"
#include "../Examples/FluTemplateDemo.h"

class FluTabBarDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluTabBarDemo(QWidget* parent = nullptr);

  protected:
    FluTabBar* tabBar;
    QVBoxLayout* m_vMainLayout;
};
