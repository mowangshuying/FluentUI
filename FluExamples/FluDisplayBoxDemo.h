#pragma once

#include <QWidget>

#include "../FluControls/FluDisplayBox.h"

class FluDisplayBoxDemo : public QWidget
{
    Q_OBJECT
  public:
    FluDisplayBoxDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        resize(600, 400);
        auto mainLayout = new QVBoxLayout;
        setLayout(mainLayout);
        auto displayBox1 = new FluDisplayBox(this);
        mainLayout->addWidget(displayBox1);
        mainLayout->addStretch();
        setStyleSheet("background-color:rgb(249,249,249);");
    }
};
