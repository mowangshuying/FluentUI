#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluPasswordBox.h"

class FluPasswordBoxDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluPasswordBoxDemo(QWidget* parent = nullptr) : FluWidget(parent)
    {
        auto passwordBox = new FluPasswordBox(this);
        passwordBox->move(50, 50);
        resize(600, 400);
    }
};
