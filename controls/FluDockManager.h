#pragma once

#include <DockManager.h>
#include <DockAreaWidget.h>
#include <DockWidget.h>
#include "../Utils/FluUtils.h"

class FluDockManager : public ads::CDockManager
{
    Q_OBJECT
  public:
    FluDockManager(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
