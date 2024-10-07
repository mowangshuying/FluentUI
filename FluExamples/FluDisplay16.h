#pragma once

#include "../FluControls/FluWidget.h"
#include "FluTemplateDemo.h"
#include <QGridLayout>

// to display widget max can display 16 wdigets.
class FluDisplay16 : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluDisplay16(QWidget* parent = nullptr);

    void addDemo(QWidget* widget);

  protected:
    QGridLayout* gridLayout;
};
