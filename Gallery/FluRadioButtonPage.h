#pragma once

#include "../Utils/FluUtils.h"
#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVRadioGroupBox.h"
#include "../Controls/FluRadioButton.h"
#include "../Controls/FluVScrollView.h"

class FluRadioButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRadioButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
