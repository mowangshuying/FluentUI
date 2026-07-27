#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluSplitButton.h"
#include "../utils/FluUtils.h"
#include "../controls/FluColorFlyout.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"

class FluSplitButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluSplitButtonPage(QWidget* parent = nullptr);

    void addSplitButtonWithText();
  public slots:
    void onThemeChanged();
};
