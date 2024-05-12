#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluSpinBox.h"
#include "../FluControls/FluDoubleSpinBox.h"

class FluSpinBoxDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluSpinBoxDemo(QWidget* parent = nullptr) : FluWidget(parent)
    {
        auto spinBox = new FluSpinBox(this);
        spinBox->move(50, 50);

        auto doubleSpinBox = new FluDoubleSpinBox(this);
        doubleSpinBox->move(50, 100);

        resize(600, 400);
    }
};
