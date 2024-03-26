#pragma once

#include <QWidget>
#include "../FluControls/FluTextEdit.h"

class FluTextEditDemo : public QWidget
{
    Q_OBJECT
  public:
    FluTextEditDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        auto textEdit = new FluTextEdit(this);
        textEdit->setFixedWidth(300);
        textEdit->move(50, 50);
        textEdit->setAutoAdjustSize(true);
        resize(600, 400);
    }
};
