#pragma once

#include "FluAEmptyPage.h"

#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluToggleSwitch.h"
#include "../Controls/FluToggleSwitchEx.h"
#include "../Controls/FluTextToggleSwitchEx.h"

class FluToggleSwitchPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluToggleSwitchPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
