#pragma once

#include "../FluControls/FluWidget.h"

#include "../FluControls/FluToggleSwitch.h"

class FluToggleSwitchDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluToggleSwitchDemo(QWidget* parent = nullptr) : FluWidget(parent)
    {
        auto toggleSwitch = new FluToggleSwitch("Off", this);
        toggleSwitch->move(50, 50);
        resize(600, 400);
    }
};
