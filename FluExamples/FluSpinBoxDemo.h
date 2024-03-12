#pragma once

#include <QWidget>
#include "../FluControls/FluSpinBox.h"
#include "../FluControls/FluDoubleSpinBox.h"

class FluSpinBoxDemo : public QWidget
{
    Q_OBJECT
  public:
    FluSpinBoxDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        auto spinBox = new FluSpinBox(this);
        spinBox->move(50, 50);

        auto doubleSpinBox = new FluDoubleSpinBox(this);
        doubleSpinBox->move(50, 100);

        resize(600, 400);
    }
};
