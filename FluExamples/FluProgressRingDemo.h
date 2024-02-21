#pragma once


#include <QWidget>
#include "../FluControls/FluProgressRing.h"

class FluProgressRingDemo : public QWidget
{
  public:
      FluProgressRingDemo(QWidget* parent = nullptr) : QWidget(parent)
      {
          auto progressRing = new FluProgressRing(this);
          progressRing->move(50, 50);
          progressRing->setCurValue(85);
          resize(600, 400);
      }
};
