#pragma once

#include <QWidget>
#include "../FluControls/FluSplitButton.h"
#include "../FluControls/FluColorFlyout.h"
#include "../FluControls/FluColorButton.h"

class FluSplitButtonDemo : public QWidget
{
    Q_OBJECT
  public:
      FluSplitButtonDemo(QWidget* parent = nullptr) : QWidget(parent)
      {
          auto splitButton = new FluSplitButton(this);
          splitButton->setText("Choose Color.");
          splitButton->move(50, 50);

          connect(splitButton, &FluSplitButton::clicked, [=]() { 
              FluColorFlyout* colorLayout = new FluColorFlyout(splitButton);
              auto colorBtn00 = new FluColorButton(QColor(255, 0, 0));
              colorLayout->addColorButton(colorBtn00, 0, 0);

              auto colorBtn01 = new FluColorButton(QColor(255, 165, 0));
              colorLayout->addColorButton(colorBtn01, 0, 1);

              auto colorBtn02 = new FluColorButton(QColor(255, 255, 0));
              colorLayout->addColorButton(colorBtn02, 0, 2);

              auto colorBtn10 = new FluColorButton(QColor(0, 128, 0));
              colorLayout->addColorButton(colorBtn10, 1, 0);

              auto colorBtn11 = new FluColorButton(QColor(75, 0, 130));
              colorLayout->addColorButton(colorBtn11, 1, 1);

              auto colorBtn12 = new FluColorButton(QColor(238, 130, 238));
              colorLayout->addColorButton(colorBtn12, 1, 2);

              auto colorBtn20 = new FluColorButton(QColor(128, 128, 128));
              colorLayout->addColorButton(colorBtn20, 2, 0);

              connect(colorLayout, &FluColorFlyout::colorChanged, [=](QColor color) {

              });
              colorLayout->show();
          });
          resize(600, 400);
      }
};
