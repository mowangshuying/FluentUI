#include "FluBusyProgressRingDemo.h"

FluBusyProgressRingDemo::FluBusyProgressRingDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    auto progressRing = new FluBusyProgressRing(this);
    progressRing->move(300 - 30, 200 - 30);

    resize(600, 400);
}
