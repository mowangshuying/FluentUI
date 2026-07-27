#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluPushButton.h"
#include "../Controls/FluToggleButton.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"

class FluToggleButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluToggleButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
