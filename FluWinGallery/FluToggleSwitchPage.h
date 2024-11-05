#pragma once

#include "FluAEmptyPage.h"

#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluToggleSwitch.h"
#include "../FluControls/FluToggleSwitchEx.h"
#include "../FluControls/FluTextToggleSwitchEx.h"

class FluToggleSwitchPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluToggleSwitchPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
