#pragma once

#include <QWidget>
#include "../FluControls/FluRatingControl.h"

class FluRatingControlDemo : public QWidget
{
    Q_OBJECT
  public:
      FluRatingControlDemo(QWidget* parent = nullptr) : QWidget(parent)
      {
          auto control = new FluRatingControl(this);
          control->move(50, 50);
          resize(600, 400);
      }
};
