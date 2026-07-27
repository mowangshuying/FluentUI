#pragma once

#include "FluAEmptyPage.h"
#include "../utils/FluUtils.h"
#include "../controls/FluHyperLinkButton.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"

class FluHyperLinkButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluHyperLinkButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
