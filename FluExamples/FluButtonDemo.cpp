#include "FluButtonDemo.h"
#include "../FluControls/FluIconButton.h"

FluButtonDemo::FluButtonDemo(QWidget *parent /*= nullptr*/) : FluDisplay9(parent)
{
    auto btn1 = new FluPushButton(this);
    btn1->setText("Standard XAML button");
    addDemo(btn1);

    auto btn2 = new FluIconButton(FluAwesomeType::Wifi, this);
    addDemo(btn2);

    auto btn3 = new FluIconButton(FluAwesomeType::Wifi, FluAwesomeType::Accept, this);
    addDemo(btn3);
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
