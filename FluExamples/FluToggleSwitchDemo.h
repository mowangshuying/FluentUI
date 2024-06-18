#pragma once

#include "../FluControls/FluWidget.h"

#include "../FluControls/FluToggleSwitch.h"
#include "../FluControls/FluToggleSwitchEx.h"

class FluToggleSwitchDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluToggleSwitchDemo(QWidget* parent = nullptr) : FluWidget(parent)
    {
        auto toggleSwitch = new FluToggleSwitch("Off", this);
        toggleSwitch->move(50, 50);

        auto toggleSwithEx = new FluToggleSwitchEx(this);
        toggleSwithEx->move(50, 100);
        resize(600, 400);
    }
};
