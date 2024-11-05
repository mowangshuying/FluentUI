#include "FluCheckBoxDemo.h"

FluCheckBoxDemo::FluCheckBoxDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    auto checkBox = new FluCheckBox("Two-State CheckBox", this);
    checkBox->move(50, 50);
    resize(600, 400);
}
