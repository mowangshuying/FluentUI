#pragma once

#include "FluAEmptyPage.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluHyperLinkButton.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"

class FluHyperLinkButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluHyperLinkButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
