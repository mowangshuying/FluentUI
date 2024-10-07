#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluLoopView.h"
#include "../FluControls/FluTimePicker24HView.h"

#include "../FluControls/FluAmPmView.h"

class FluLoopViewDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluLoopViewDemo(QWidget* parent = nullptr);
};
