#include "FluDropDownButtonDemo.h"

FluDropDownButtonDemo::FluDropDownButtonDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    auto dropDownButton = new FluDropDownButton(this);
    dropDownButton->setText("Email");

    dropDownButton->addTextItem("Send");
    dropDownButton->addTextItem("Reply");
    dropDownButton->addTextItem("Reply All");

    dropDownButton->move(50, 50);
    resize(600, 400);

    setStyleSheet("background-color:rgb(243,243,243);");
}
