#pragma once

#include "../utils/FluUtils.h"
#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVRadioGroupBox.h"
#include "../controls/FluRadioButton.h"
#include "../controls/FluVScrollView.h"

class FluRadioButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRadioButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
