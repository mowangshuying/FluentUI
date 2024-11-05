#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluSlider.h"
#include "../FluControls/FluVScrollView.h"

class FluSliderPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluSliderPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
