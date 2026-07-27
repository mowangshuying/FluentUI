#pragma once

#include "../controls/FluWidget.h"
#include "../controls/FluLoopView.h"
#include "../controls/FluTimePicker24HView.h"

#include "../controls/FluAmPmView.h"

class FluLoopViewDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluLoopViewDemo(QWidget* parent = nullptr);
};
