#include "FluToolTipDemo.h"
#include <QHBoxLayout>

FluToolTipDemo::FluToolTipDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    QHBoxLayout* hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->setContentsMargins(40, 40, 40, 40);
    hBoxLayout->setSpacing(30);

    auto btn1 = new FluPushButton(tr("Simple"), this);
    FluToolTip::setToolTip(this, btn1, "A simple tooltip.");
    hBoxLayout->addWidget(btn1);

    auto btn2 = new FluPushButton(tr("Multiline"), this);
    FluToolTip::setToolTip(this, btn2, "This tooltip has\nmultiple lines of\ndescriptive text.");
    hBoxLayout->addWidget(btn2);

    auto btn3 = new FluPushButton(tr("Long text"), this);
    FluToolTip::setToolTip(this, btn3,
                           "A longer tooltip that demonstrates the maximum\n"
                           "width constraint and how text wraps gracefully\n"
                           "across several lines.");
    hBoxLayout->addWidget(btn3);

    resize(600, 400);
}
