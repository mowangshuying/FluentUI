#include "FluColorViewDemo.h"

FluColorViewDemo::FluColorViewDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    // auto colorView = new FluColorView(this);
    // colorView->move(50, 50);

    auto btn = new FluPushButton(this);
    btn->setFixedSize(120, 30);
    btn->setText("Click Me!");

    // btn->move(300, 400);
    m_contentLayout->setAlignment(Qt::AlignCenter);
    m_contentLayout->addWidget(btn);

    connect(btn, &FluPushButton::clicked, [=]() {
        FluColorView view(window());
        view.exec();
    });
}
