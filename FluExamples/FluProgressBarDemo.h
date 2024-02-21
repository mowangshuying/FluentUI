#pragma once

#include <QWidget>
#include "../FluControls/FluProgressBar.h"

class FluProgressBarDemo : public QWidget
{
	Q_OBJECT
  public:
	  FluProgressBarDemo(QWidget* parent = nullptr) : QWidget(parent)
	  {
          auto progressBar = new FluProgressBar(this);
          progressBar->move(50, 50);
          progressBar->setValue(75);
          progressBar->setFixedWidth(150);

          resize(600, 400);
	  }
};
