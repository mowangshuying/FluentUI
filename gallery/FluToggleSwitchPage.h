#pragma once

#include "FluAEmptyPage.h"

#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluToggleSwitch.h"
#include "../controls/FluToggleSwitchEx.h"
#include "../controls/FluTextToggleSwitchEx.h"

class FluToggleSwitchPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluToggleSwitchPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
