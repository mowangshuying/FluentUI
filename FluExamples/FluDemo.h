#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluFrameLessWidget.h"

class FluDemo : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    FluDemo(QWidget* parent = nullptr);
  public slots:
    void onThemeChanged();
};
