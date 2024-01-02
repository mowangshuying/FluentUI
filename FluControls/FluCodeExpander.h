#pragma once

#include "FluExpander.h"
#include <QWidget>

class FluCodeExpander : public FluExpander
{
    Q_OBJECT
  public:
      FluCodeExpander(QWidget* parent = nullptr) : FluExpander(parent)
      {

      }
};
