#pragma once

#include "FluAEmptyPage.h"
#include "../utils/FluUtils.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluSlider.h"
#include "../controls/FluVScrollView.h"

class FluSliderPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluSliderPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
