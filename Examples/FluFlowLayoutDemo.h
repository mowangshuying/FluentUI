#pragma once

#include "../Controls/FluWidget.h"
#include "../Controls/FluFlowLayout.h"
#include <QPushButton>
#include "../Controls/FluVScrollView.h"

// take it from Qt examples
class FluFlowLayoutDemo : public FluVScrollView
{
  public:
    FluFlowLayoutDemo(QWidget* parent = nullptr);
};
