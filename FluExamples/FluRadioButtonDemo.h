#pragma once

#include "../FluControls/FluRadioButton.h"
#include "../FluControls/FluVRadioGroupBox.h"
#include "../FluControls/FluWidget.h"
#

class FluRadioButtonDemo : public FluWidget
{
  public:
    FluRadioButtonDemo(QWidget* parent = nullptr) : FluWidget(parent)
    {
        resize(600, 400);
        FluVRadioGroupBox* group = new FluVRadioGroupBox("Options", this);
        group->move(50, 50);
        // group->setExclusive(true);

        auto btn1 = new FluRadioButton("Option 1", group);
        auto btn2 = new FluRadioButton("Option 2", group);
        auto btn3 = new FluRadioButton("Option 3", group);

        // group->addButton(btn1);
        // group->addButton(btn2);
        // group->addButton(btn3);

        group->addRadioButton(btn1);
        group->addRadioButton(btn2);
        group->addRadioButton(btn3);
    }
};
