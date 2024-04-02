#pragma once

#include <QWidget>
#include "../FluControls/FluComboBox.h"
#include "../FluControls/FluComboBoxEx.h"
class FluComboBoxDemo : public QWidget
{
    Q_OBJECT
  public:
    FluComboBoxDemo(QWidget* parent = nullptr) : QWidget(parent)
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
