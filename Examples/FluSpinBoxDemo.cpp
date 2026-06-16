#include "FluSpinBoxDemo.h"

FluSpinBoxDemo::FluSpinBoxDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    auto spinBox = new FluSpinBox(this);
    spinBox->move(50, 50);

    auto doubleSpinBox = new FluDoubleSpinBox(this);
    doubleSpinBox->move(50, 100);

    resize(600, 400);
}
