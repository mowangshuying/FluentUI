#include "FluDisplayCodeDemo.h"

FluDisplayCodeDemo::FluDisplayCodeDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    auto display = new FluCodeBox(this);
    display->setFixedSize(300, 50);
    display->move(50, 50);

    QString code = "std::cout << \"hello, world\" << std::endl; // this just a text";
    display->setCodeText(code);
    setStyleSheet("background-color:rgb(249, 249, 249);");
}
