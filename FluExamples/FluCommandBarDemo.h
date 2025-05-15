#pragma once

#include "FluTemplateDemo.h"
#include "../FluControls/FluCommandBar.h"
#include "../FluControls/FluCommandBarIconTextItem.h"

class FluCommandBarDemo : public FluTemplateDemo
{
	Q_OBJECT
  public:
	  FluCommandBarDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
	  {
              auto commandBar = new FluCommandBar;
	  }
};
