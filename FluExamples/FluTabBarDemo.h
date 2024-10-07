#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluTabBarContent.h"
#include <QVBoxLayout>
#include "../FluControls/FluTabBarItem.h"
#include "../FluControls/FluTabBar.h"

class FluTabBarDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluTabBarDemo(QWidget* parent = nullptr);

    // void resizeEvent(QResizeEvent* event)
    //{
    //       tabBar->setFixedWidth(width());
    // }

  protected:
    FluTabBar* tabBar;
    QVBoxLayout* m_vMainLayout;
};
