#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluBusyProgressRing.h"
#include "FluTemplateDemo.h"

class FluBusyProgressRingDemo : public FluTemplateDemo
{
  public:
    FluBusyProgressRingDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
    {
        auto progressRing = new FluBusyProgressRing(this);
        progressRing->move(300 - 30, 200 - 30);

        resize(600, 400);
    }
};
