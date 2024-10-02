#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluCheckBox.h"
#include "FluTemplateDemo.h"

class FluCheckBoxDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluCheckBoxDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
    {
        auto checkBox = new FluCheckBox("Two-State CheckBox", this);
        checkBox->move(50, 50);
        resize(600, 400);
    }
};
