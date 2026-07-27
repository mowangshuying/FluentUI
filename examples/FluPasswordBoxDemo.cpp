#include "FluPasswordBoxDemo.h"

FluPasswordBoxDemo::FluPasswordBoxDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    auto passwordBox = new FluPasswordBox(this);
    passwordBox->move(50, 50);
    resize(600, 400);
}
