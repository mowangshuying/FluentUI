#include "FluToggleSwitchDemo.h"

FluToggleSwitchDemo::FluToggleSwitchDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    auto switch1 = new FluToggleSwitch(this);
    switch1->move(50, 50);

    auto switch2 = new FluToggleSwitch(this);
    switch2->setEmptyText(true);
    switch2->move(50, 100);

    auto switch3 = new FluToggleSwitch(this);
    switch3->setTextPosition(TextPosition::Left);
    switch3->move(50, 150);

    resize(600, 400);
}
