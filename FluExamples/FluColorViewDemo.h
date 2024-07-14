#pragma once

#include "FluTemplateDemo.h"
#include "../FluControls/FluColorViewGradient.h"
#include "../FluControls/FluColorViewVHandle.h"
#include "../FluControls/FluColorViewHHandle.h"
#include "../FluControls/FluLabel.h"
#include "../FluControls/FluLineEdit.h"
#include "../FluControls/FluColorView.h"

class FluColorViewDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
      FluColorViewDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
      {
          auto colorView = new FluColorView(this);
          colorView->move(50, 50);
      }
};
