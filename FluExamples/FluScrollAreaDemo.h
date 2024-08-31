#pragma once

#include "../FluControls/FluScrollArea.h"
#include "../FluControls/FluImageBox.h"

class FluScrollAreaDemo : public FluScrollArea
{
    Q_OBJECT
  public:
    FluScrollAreaDemo(QWidget* parent = nullptr) : FluScrollArea(parent)
    {
        QPixmap img("../res/GalleryHeaderImage.png");
        auto imgBox = new FluImageBox(img, this);
        imgBox->setFixedSize(img.size());
        setWidget(imgBox);

        resize(600, 400);
        setStyleSheet("QScrollArea {border: none;}");
    }
};
