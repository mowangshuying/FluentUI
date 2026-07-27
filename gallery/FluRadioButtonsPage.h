#pragma once

#include "../controls/FluHRadioGroupBox.h"
#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluBorder.h"

class FluRadioButtonsPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRadioButtonsPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
