#pragma once

#include <QWidget>
#include "../FluControls/FluSpinBox.h"

class FluSpinBoxDemo : public QWidget
{
    Q_OBJECT
  public:
    FluSpinBoxDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        auto spinBox = new FluSpinBox(this);
        spinBox->move(50, 50);
    }
};
