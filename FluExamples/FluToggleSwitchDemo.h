#pragma once

#include <QWidget>

#include "../FluControls/FluToggleSwitch.h"

class FluToggleSwitchDemo : public QWidget
{
    Q_OBJECT
  public:
    FluToggleSwitchDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        auto checkBox = new FluToggleSwitch("Off", this);
        checkBox->move(50, 50);
        resize(600, 400);
    }
};
