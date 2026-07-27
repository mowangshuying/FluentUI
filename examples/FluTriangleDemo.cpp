#include "FluTriangleDemo.h"

FluTriangleDemo::FluTriangleDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    auto triangle = new FluTriangle(this);
    triangle->move(100, 100);
}
