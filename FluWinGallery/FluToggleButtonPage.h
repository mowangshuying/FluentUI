#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluToggleButton.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluToggleButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluToggleButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
