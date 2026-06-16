#include "FluTextEditDemo.h"

FluTextEditDemo::FluTextEditDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    auto textEdit = new FluTextEdit(this);
    textEdit->setFixedWidth(300);
    textEdit->move(50, 50);
    textEdit->setAutoAdjustSize(true);
    resize(600, 400);
}
