#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluHyperLinkButton.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluHyperLinkButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluHyperLinkButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
