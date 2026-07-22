#pragma once

#include "FluWidget.h"

enum class FluTeachingTipPosition
{
    Top,
    Bottom,
    Left,
    Right,
};

class FluTeachingTip : public FluWidget
{
    Q_OBJECT
  public:
    FluTeachingTip(QWidget* parent = nullptr) : FluWidget(parent)
    {
    }
};
