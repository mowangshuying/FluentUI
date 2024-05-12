#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluComboBox.h"
#include "../FluControls/FluComboBoxEx.h"
class FluComboBoxDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluComboBoxDemo(QWidget* parent = nullptr) : FluWidget(parent)
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
};
