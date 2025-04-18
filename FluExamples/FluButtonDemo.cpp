#include "FluButtonDemo.h"
#include "../FluControls/FluIconButton.h"
#include "../FluControls/FluToggleButton.h"
#include "../FluControls/FluRotationButton.h"
#include "../FluUtils/FluIconUtils.h"
#include "../FluControls/FluRadioButton.h"
#include "../FluControls/FluHyperLinkButton.h"
#include "../FluControls/FluRepeatButton.h"
#include "../FluControls/FluAppBarButton.h"
#include "../FluControls/FluAppBarToggleButton.h"
#include "../FluControls/FluPPushButton.h"
#include "../FluControls/FluScaleButton.h"

FluButtonDemo::FluButtonDemo(QWidget *parent /*= nullptr*/) : FluDisplay16(parent)
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

    auto btn7 = new FluHyperLinkButton("https://github.com/mowangshuying/FluentUI");
    btn7->setText("FluentUI Repo Home Page");
    addDemo(btn7);

    auto btn8 = new FluRepeatButton;
    btn8->setText("Click and Holder");
    addDemo(btn8);

    auto btn9 = new FluAppBarButton(FluAwesomeType::Like);
    btn9->setText("SymbolIcon");
    addDemo(btn9);

    auto btn10 = new FluAppBarToggleButton(FluAwesomeType::Like);
    btn10->setText("SymbolIcon");
    addDemo(btn10);

    auto btn11 = new FluPPushButton;
    btn11->setText("Paint Button");
    addDemo(btn11);

    auto btn12 = new FluScaleButton(FluAwesomeType::Search);
    addDemo(btn12);
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
