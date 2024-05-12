#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluCheckBox.h"

class FluCheckBoxDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluCheckBoxDemo(QWidget* parent = nullptr) : FluWidget(parent)
    {
        auto checkBox = new FluCheckBox("Two-State CheckBox", this);
        checkBox->move(50, 50);
        resize(600, 400);
    }
};
