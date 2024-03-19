#pragma once

#include <QWidget>

#include "../FluControls/FluFlyout.h"
#include "../FluControls/FluPushButton.h"

class FluFlyoutDemo : public QWidget
{
    Q_OBJECT
  public:
      FluFlyoutDemo(QWidget* parent = nullptr)
      {
          auto btn = new FluPushButton(this);
          
          btn->setText("Empty cart");
          btn->move(200, 200);

          connect(btn, &FluPushButton::clicked, [=]() { 
              FluFlyout::setFlyout(btn, parent);
              });

          resize(600, 400);
      }
};
