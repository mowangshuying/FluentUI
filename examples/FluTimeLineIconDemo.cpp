#include "FluTimeLineIconDemo.h"

FluTimeLineIconDemo::FluTimeLineIconDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    for (int i = 0; i < 8; i++)
    {
        auto timeLineIcon = new FluTimeLineIcon(this);
        timeLineIcon->move(200, 200 + i * 40);
    }
}
