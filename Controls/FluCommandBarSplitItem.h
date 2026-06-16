#pragma once

#include "FluCommandBarItem.h"

class FluCommandBarSplitItem : public FluCommandBarItem
{
    Q_OBJECT
  public:
    FluCommandBarSplitItem(QWidget* parent = nullptr) : FluCommandBarItem(parent)
    {
    }
};
