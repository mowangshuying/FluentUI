#include "FluDisplayIconBoxDemo.h"

FluDisplayIconBoxDemo::FluDisplayIconBoxDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    setStyleSheet("background-color:rgb(243,243,243);");
    resize(600, 400);

    auto iconBox = new FluDisplayIconBox(FluAwesomeType::Wifi, this);
    iconBox->move(50, 50);
}
