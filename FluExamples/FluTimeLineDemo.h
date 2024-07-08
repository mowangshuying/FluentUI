#pragma once

#include "FluTemplateDemo.h"
#include "../FluControls/FluTimeLine.h"

class FluTimeLineDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
      FluTimeLineDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
      {
          auto timeLine = new FluTimeLine;
          timeLine->addTimeLineItem("Create a services site 2015-09-01");
          
          timeLine->addTimeLineItem("Create a services size 2015-09-01");

          timeLine->addTimeLineItem("Solve inital network problems1");
          timeLine->addTimeLineItem(2, "Solve inital network problems2");
          timeLine->addTimeLineItem(2, "Solve inital network problems3");

          timeLine->addTimeLineItem("Technical testing 1");
          timeLine->addTimeLineItem(3, "Technical testing 1");
          timeLine->addTimeLineItem(3, "Technical testing 1");

          m_contentLayout->addWidget(timeLine);
      }
};
