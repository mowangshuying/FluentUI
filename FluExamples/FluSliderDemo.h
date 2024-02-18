#pragma once

#include <QWidget>
#include "../FluControls/FluSlider.h"

class FluSliderDemo : public QWidget
{
  public:
      FluSliderDemo(QWidget* parent = nullptr) : QWidget(parent)
      {
          FluSlider* hSlider = new FluSlider(this);
          hSlider->setOrientation(Qt::Horizontal);
          hSlider->setMinimum(0);
          hSlider->setMaximum(100);
          hSlider->setSingleStep(10);

          hSlider->move(50, 50);
          resize(600, 400);
      }
};
