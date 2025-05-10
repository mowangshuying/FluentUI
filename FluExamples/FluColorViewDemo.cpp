#include "FluColorViewDemo.h"
#include "../FluControls/FluColorButton.h"
#include "../FluControls/FluColorPickerButton.h"

FluColorViewDemo::FluColorViewDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    // auto colorView = new FluColorView(this);
    // colorView->move(50, 50);

    auto colorBtn = new FluColorPickerButton(this);
   // colorBtn->move(60, 30);
    

    //auto btn = new FluPushButton(this);
    //btn->setFixedSize(120, 30);
    //btn->setText("Click Me!");

    // btn->move(300, 400);
    m_contentLayout->setAlignment(Qt::AlignCenter);
    m_contentLayout->addWidget(colorBtn);

    connect(colorBtn, &FluPushButton::clicked, [=]() {
        FluColorView view(window());
        view.exec();
        colorBtn->setColor(view.getColor());
    });
}
