#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDropDownButton.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluDropDownButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluDropDownButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
