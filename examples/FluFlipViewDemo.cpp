#include "FluFlipViewDemo.h"

FluFlipViewDemo::FluFlipViewDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setFixedSize(600 * 2, 400);

    {
        auto flipView = new FluHFlipView(this);
        flipView->move(50, 50);
        // resize(800, 600);

        flipView->addPixmap(FluIconUtils::getPixmap(("../res/SampleMedia/cliff.jpg")));
        flipView->addPixmap(FluIconUtils::getPixmap(("../res/SampleMedia/grapes.jpg")));
        // LandscapeImage8.jpg
        flipView->addPixmap(FluIconUtils::getPixmap(("../res/SampleMedia/LandscapeImage8.jpg")));
        flipView->addPixmap(FluIconUtils::getPixmap(("../res/SampleMedia/sunset.jpg")));
    }

    {
        auto flipView = new FluVFlipView(this);
        flipView->move(50 + 600, 50);
        // resize(800, 600);

        flipView->addPixmap(FluIconUtils::getPixmap(("../res/SampleMedia/cliff.jpg")));
        flipView->addPixmap(FluIconUtils::getPixmap(("../res/SampleMedia/grapes.jpg")));
        // LandscapeImage8.jpg
        flipView->addPixmap(FluIconUtils::getPixmap(("../res/SampleMedia/LandscapeImage8.jpg")));
        flipView->addPixmap(FluIconUtils::getPixmap(("../res/SampleMedia/sunset.jpg")));
    }
}
