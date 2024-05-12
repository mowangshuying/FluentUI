#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluRatingControl.h"

class FluRatingControlDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluRatingControlDemo(QWidget* parent = nullptr) : FluWidget(parent)
    {
        auto control = new FluRatingControl(this);
        control->move(50, 50);
        resize(600, 400);
    }
};
