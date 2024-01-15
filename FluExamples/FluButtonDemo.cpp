#include "FluButtonDemo.h"
#include "../FluControls/FluIconButton.h"
#include "../FluControls/FluToggleButton.h"
#include "../FluControls/FluRotationButton.h"
#include "../FluUtils/FluIconUtils.h"
#include "../FluControls/FluRadioButton.h"

FluButtonDemo::FluButtonDemo(QWidget *parent /*= nullptr*/) : FluDisplay9(parent)
{
    auto btn1 = new FluPushButton(this);
    btn1->setText("Standard XAML button");
    addDemo(btn1);

    auto btn2 = new FluIconButton(FluAwesomeType::Wifi, this);
    addDemo(btn2);

    auto btn3 = new FluIconButton(FluAwesomeType::Wifi, FluAwesomeType::Accept, this);
    addDemo(btn3);

    auto btn4 = new FluToggleButton;
    btn4->setText("ToggleButton");
    addDemo(btn4);

    //  auto btn5 = new FluRotationButton;
    //  btn5->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Settings));
    //  btn5->setIconSize(QSize(22, 22));
    //  btn5->setFixedSize(30, 30);
    //  btn5->setRotation(true);
    //  addDemo(btn5);

    auto btn6 = new FluRadioButton;
    addDemo(btn6);
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
