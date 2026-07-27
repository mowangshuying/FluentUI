#include "FluDisplayBoxDemo.h"

FluDisplayBoxDemo::FluDisplayBoxDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    resize(600, 400);
    auto mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    auto displayBox1 = new FluDisplayBox(this);
    mainLayout->addWidget(displayBox1);
    // mainLayout->addStretch()

    auto displayBox2 = new FluDisplayBoxEx(this);
    mainLayout->addWidget(displayBox2);

    setStyleSheet("background-color:rgb(249,249,249);");
    mainLayout->addStretch();
}
