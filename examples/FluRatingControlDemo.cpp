#include "FluRatingControlDemo.h"

FluRatingControlDemo::FluRatingControlDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    auto control = new FluRatingControl(this);
    control->move(50, 50);
    resize(600, 400);
}
