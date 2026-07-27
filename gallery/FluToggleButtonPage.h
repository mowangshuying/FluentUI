#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluPushButton.h"
#include "../controls/FluToggleButton.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"

class FluToggleButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluToggleButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
