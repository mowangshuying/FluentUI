#pragma once

#include "../FluUtils/FluUtils.h"
#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVRadioGroupBox.h"
#include "../FluControls/FluRadioButton.h"
#include "../FluControls/FluVScrollView.h"

class FluRadioButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRadioButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
