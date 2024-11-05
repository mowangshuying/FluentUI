#pragma once

#include "../FluControls/FluHRadioGroupBox.h"
#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluBorder.h"

class FluRadioButtonsPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRadioButtonsPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
