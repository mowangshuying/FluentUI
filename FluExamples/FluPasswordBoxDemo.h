#pragma once

#include <QWidget>
#include "../FluControls/FluPasswordBox.h"

class FluPasswordBoxDemo : public QWidget
{
	Q_OBJECT
  public:
	  FluPasswordBoxDemo(QWidget* parent = nullptr) : QWidget(parent)
	  {
              auto passwordBox = new FluPasswordBox(this);
              passwordBox->move(50, 50);
              resize(600, 400);
	  }
};
