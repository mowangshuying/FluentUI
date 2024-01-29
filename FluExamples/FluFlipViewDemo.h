#pragma once

#include <QWidget>
#include "../FluControls/FluFlipView.h"

class FluFlipViewDemo : public QWidget
{
  public:
      FluFlipViewDemo(QWidget* parent = nullptr) : QWidget(parent)
      {
          setFixedSize(600, 400);
          auto flipView = new FluFlipView(this);
          flipView->move(50, 50);
          //resize(800, 600);

          flipView->addPixmap(QPixmap("../res/SampleMedia/cliff.jpg"));
          flipView->addPixmap(QPixmap("../res/SampleMedia/grapes.jpg"));
          //LandscapeImage8.jpg
          flipView->addPixmap(QPixmap("../res/SampleMedia/LandscapeImage8.jpg"));
          flipView->addPixmap(QPixmap("../res/SampleMedia/sunset.jpg"));
      }
};
