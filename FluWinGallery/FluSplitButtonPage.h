#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluSplitButton.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluColorFlyout.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluSplitButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluSplitButtonPage(QWidget* parent = nullptr);

    void addSplitButtonWithText();
  public slots:
    void onThemeChanged();
};
