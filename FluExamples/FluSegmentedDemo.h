#pragma once

#include "FluTemplateDemo.h"
#include "../FluControls/FluSegmented.h"

class FluSegmentedDemo : public FluTemplateDemo
{
  public:
      FluSegmentedDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
      {
          auto segmented = new FluSegmented(this);
          segmented->setFixedWidth(300);

          // song;
          auto songSegmentedItem = new FluSegmentedItem;
          songSegmentedItem->setText("Song");
          segmented->addWidget(songSegmentedItem);

          // albnum;
          auto albnumSegmentedItem = new FluSegmentedItem;
          albnumSegmentedItem->setText("Albnum");
          segmented->addWidget(albnumSegmentedItem);

          // artist;
          auto artistSegmentedItem = new FluSegmentedItem;
          artistSegmentedItem->setText("Artist");
          segmented->addWidget(artistSegmentedItem);

          // set Song;
          segmented->setCurrentItem("Song");

          //m_contentLayout->addWidget(segmented);
          segmented->move(200, 200);
      }
};
