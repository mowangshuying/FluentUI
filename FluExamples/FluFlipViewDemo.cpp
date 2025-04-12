#include "FluFlipViewDemo.h"

FluFlipViewDemo::FluFlipViewDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setFixedSize(600 * 2, 400);

    {
        auto flipView = new FluHFlipView(this);
        flipView->move(50, 50);
        // resize(800, 600);

        flipView->addPixmap(QPixmap(FLURC("res/SampleMedia/cliff.jpg")));
        flipView->addPixmap(QPixmap(FLURC("res/SampleMedia/grapes.jpg")));
        // LandscapeImage8.jpg
        flipView->addPixmap(QPixmap(FLURC("res/SampleMedia/LandscapeImage8.jpg")));
        flipView->addPixmap(QPixmap(FLURC("res/SampleMedia/sunset.jpg")));
    }

    {
        auto flipView = new FluVFlipView(this);
        flipView->move(50 + 600, 50);
        // resize(800, 600);

        flipView->addPixmap(QPixmap(FLURC("res/SampleMedia/cliff.jpg")));
        flipView->addPixmap(QPixmap(FLURC("res/SampleMedia/grapes.jpg")));
        // LandscapeImage8.jpg
        flipView->addPixmap(QPixmap(FLURC("res/SampleMedia/LandscapeImage8.jpg")));
        flipView->addPixmap(QPixmap(FLURC("res/SampleMedia/sunset.jpg")));
    }
}
