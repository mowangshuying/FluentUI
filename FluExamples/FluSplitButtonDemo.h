#pragma once

#include <QWidget>
#include "../FluControls/FluSplitButton.h"

class FluSplitButtonDemo : public QWidget
{
    Q_OBJECT
  public:
      FluSplitButtonDemo(QWidget* parent = nullptr) : QWidget(parent)
      {
          auto splitButton = new FluSplitButton(this);
          splitButton->move(50, 50);
          resize(600, 400);
      }
};
