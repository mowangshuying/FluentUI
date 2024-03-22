#pragma once

#include <QWidget>

#include "../FluControls/FluToggleSwitch.h"

class FluToggleSwitchDemo : public QWidget
{
    Q_OBJECT
  public:
    FluToggleSwitchDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        auto toggleSwitch = new FluToggleSwitch("Off", this);
        toggleSwitch->move(50, 50);
        resize(600, 400);
    }
};
