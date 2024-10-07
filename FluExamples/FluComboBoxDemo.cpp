#include "FluComboBoxDemo.h"

FluComboBoxDemo::FluComboBoxDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    auto comboBoxEx = new FluComboBoxEx(this);
    comboBoxEx->setFixedWidth(120);
    comboBoxEx->move(50, 50);

    comboBoxEx->addItem("Blue");
    comboBoxEx->addItem("Green");
    comboBoxEx->addItem("Red");
    comboBoxEx->addItem("Yellow");

    resize(600, 400);
    setStyleSheet("background-color: rgb(249, 249, 249);");
}
