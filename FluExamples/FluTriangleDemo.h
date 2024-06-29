#pragma once

#include "../FluControls/FluTriangle.h"
#include "FluTemplateDemo.h"

class FluTriangleDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluTriangleDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
    {
        auto triangle = new FluTriangle(this);
        triangle->move(100, 100);
    }
};
