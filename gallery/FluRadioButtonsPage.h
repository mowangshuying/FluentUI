#pragma once

#include "../Controls/FluHRadioGroupBox.h"
#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluBorder.h"

class FluRadioButtonsPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRadioButtonsPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
