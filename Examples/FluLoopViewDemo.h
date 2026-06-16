#pragma once

#include "../Controls/FluWidget.h"
#include "../Controls/FluLoopView.h"
#include "../Controls/FluTimePicker24HView.h"

#include "../Controls/FluAmPmView.h"

class FluLoopViewDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluLoopViewDemo(QWidget* parent = nullptr);
};
