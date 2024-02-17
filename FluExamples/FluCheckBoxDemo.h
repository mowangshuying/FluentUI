#pragma once

#include <QWidget>
#include "../FluControls/FluCheckBox.h"

class FluCheckBoxDemo : public QWidget
{
	Q_OBJECT
  public:
	  FluCheckBoxDemo(QWidget* parent = nullptr) : QWidget(parent)
	  {
              auto checkBox = new FluCheckBox("Two-State CheckBox", this);
			  checkBox->move(50, 50);
              resize(600, 400);
	  }
};
