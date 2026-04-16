#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluTabBarContent.h"
#include <QVBoxLayout>
#include "../FluControls/FluTabBarItem.h"
#include "../FluControls/FluTabBar.h"
#include "../FluExamples/FluTemplateDemo.h"

class FluTabBarDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluTabBarDemo(QWidget* parent = nullptr);

  protected:
    FluTabBar* tabBar;
    QVBoxLayout* m_vMainLayout;
};
