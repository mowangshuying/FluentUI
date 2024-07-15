#pragma once

#include "FluTemplateDemo.h"
#include "../FluControls/FluColorViewGradient.h"
#include "../FluControls/FluColorViewVHandle.h"
#include "../FluControls/FluColorViewHHandle.h"
#include "../FluControls/FluLabel.h"
#include "../FluControls/FluLineEdit.h"
#include "../FluControls/FluColorView.h"
#include "../FluControls/FluPushButton.h"

class FluColorViewDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
      FluColorViewDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
      {
          //auto colorView = new FluColorView(this);
          //colorView->move(50, 50);

          auto btn = new FluPushButton(this);
          btn->setFixedSize(120, 30);
          btn->setText("Click Me!");

          btn->move(200, 200);

          connect(btn, &FluPushButton::clicked, [=]() { 
              FluColorView view(window());
              view.exec();
          });
      }
};
