#pragma once

#include "../controls/FluWidget.h"
#include "../controls/FluFlowLayout.h"
#include <QPushButton>
#include "../controls/FluVScrollView.h"

// take it from Qt examples
class FluFlowLayoutDemo : public FluVScrollView
{
  public:
    FluFlowLayoutDemo(QWidget* parent = nullptr);
};
