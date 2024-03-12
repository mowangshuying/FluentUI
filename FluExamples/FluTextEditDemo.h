#pragma once

#include <QWidget>
#include "../FluControls/FluTextEdit.h"

class FluTextEditDemo : public QWidget
{
	Q_OBJECT
  public:
	  FluTextEditDemo(QWidget* parent = nullptr) : QWidget(parent)
	  {
              auto textEdit = new FluTextEdit(this);
              textEdit->setFixedSize(500, 300);
			  textEdit->move(50, 50);
			  resize(600, 400);
	  }
};
