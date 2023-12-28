#include "FluButtonDemo.h"

FluButtonDemo::FluButtonDemo(QWidget *parent /*= nullptr*/) : QWidget(parent)
{
    auto btn1 = new FluPushButton(this);
    btn1->setText("Standard XAML button");
    btn1->move(50, 50);
    setStyleSheet("background-color:rgb(243,243,243);");
}

void FluButtonDemo::paintEvent(QPaintEvent *paintEvent)
{
    QWidget::paintEvent(paintEvent);
    QStyleOption opt;
    // opt.init(this);
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
