#include "FluRatingControlDemo.h"

#include <QLabel>

FluRatingControlDemo::FluRatingControlDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    auto control = new FluRatingControl(this);
    control->move(50, 50);
    control->setValue(3.5);

    auto label = new QLabel(this);
    label->move(50, 100);
    label->setText(QString("Value: %1").arg(control->getValue()));
    connect(control, &FluRatingControl::valueChanged, this, [label](double v) { label->setText(QString("Value: %1").arg(v)); });

    resize(600, 400);
}
