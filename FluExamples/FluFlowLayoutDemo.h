#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluFlowLayout.h"
#include <QPushButton>
#include "../FluControls/FluVScrollView.h"

// take it from Qt examples
class FluFlowLayoutDemo : public FluVScrollView
{
  public:
    FluFlowLayoutDemo(QWidget* parent = nullptr);
};
