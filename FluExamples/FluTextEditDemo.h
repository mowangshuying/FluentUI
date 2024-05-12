#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluTextEdit.h"

class FluTextEditDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluTextEditDemo(QWidget* parent = nullptr) : FluWidget(parent)
    {
        auto textEdit = new FluTextEdit(this);
        textEdit->setFixedWidth(300);
        textEdit->move(50, 50);
        textEdit->setAutoAdjustSize(true);
        resize(600, 400);
    }
};
