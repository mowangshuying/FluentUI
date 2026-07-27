#include "FluLoopViewDemo.h"

FluLoopViewDemo::FluLoopViewDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    auto timePicker24HView = new FluTimePicker24HView(this);
    timePicker24HView->move(50, 50);

    auto amPmView = new FluAmPmView(80, this);
    amPmView->move(200, 50);
    amPmView->setFixedHeight(300);

    resize(800, 800);
}
