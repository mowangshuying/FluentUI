#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluSplitButton.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluColorFlyout.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"

class FluSplitButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluSplitButtonPage(QWidget* parent = nullptr);

    void addSplitButtonWithText();
  public slots:
    void onThemeChanged();
};
