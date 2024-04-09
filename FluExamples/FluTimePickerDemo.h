#pragma once

#include <QWidget>
#include "../FluControls/FluTimePicker24H.h"

class FluTimePickerDemo : public QWidget
{
    Q_OBJECT
  public:
      FluTimePickerDemo(QWidget* parent = nullptr) : QWidget(parent)
      {
          auto timePicker24H = new FluTimePicker24H(this);
          timePicker24H->move(300 - timePicker24H->width() / 2, 200 - timePicker24H->height() / 2);
          resize(600, 400);
      }

  protected:

};
