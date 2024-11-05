#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluRepeatButton.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluVScrollView.h"

class FluRepeatButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRepeatButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
