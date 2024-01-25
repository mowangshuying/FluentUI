#pragma once

#include <QWidget>
#include "../FluControls/FluComboBox.h"
class FluComboBoxDemo : public QWidget
{
    Q_OBJECT
  public:
    FluComboBoxDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        auto comboBox = new FluComboBox(this);
        comboBox->move(50, 50);

        comboBox->addItem("Blue");
        comboBox->addItem("Green");
        comboBox->addItem("Red");
        comboBox->addItem("Yellow");

        resize(600, 400);
        setStyleSheet("background-color: rgb(249, 249, 249);");
    }
};
