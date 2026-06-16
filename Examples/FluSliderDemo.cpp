#include "FluSliderDemo.h"

FluSliderDemo::FluSliderDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    FluSlider* hSlider = new FluSlider(this);
    hSlider->setOrientation(Qt::Horizontal);
    hSlider->setMinimum(0);
    hSlider->setMaximum(100);
    hSlider->setSingleStep(10);
    hSlider->move(50, 50);

    FluSlider* vSlider = new FluSlider(this);
    // vSlider->setInvertedAppearance(false);
    vSlider->setOrientation(Qt::Vertical);
    vSlider->setMinimum(0);
    vSlider->setMaximum(100);
    vSlider->setSingleStep(5);
    vSlider->move(250, 50);

    resize(600, 400);
}
