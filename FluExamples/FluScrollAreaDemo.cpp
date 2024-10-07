#include "FluScrollAreaDemo.h"

FluScrollAreaDemo::FluScrollAreaDemo(QWidget* parent /*= nullptr*/) : FluScrollArea(parent)
{
    QPixmap img("../res/SampleMedia/LandscapeImage9.jpg");
    auto imgBox = new FluImageBox(img, this);
    imgBox->setFixedSize(2000, 2000);
    setWidget(imgBox);

    resize(600, 600);
    setStyleSheet("QScrollArea {border: none;}");
}
