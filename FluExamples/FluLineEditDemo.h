#pragma once

#include <QLineEdit>

#include "../FluControls/FluLineEdit.h"
#include "FluDisplay9.h"

class FluLineEditDemo : public FluDisplay9
{
    Q_OBJECT
  public:
    FluLineEditDemo(QWidget* parent = nullptr) : FluDisplay9(parent)
    {
        auto lineEdit = new FluLineEdit(this);
        lineEdit->setFixedSize(120, 30);
        addDemo(lineEdit);
    }
};
