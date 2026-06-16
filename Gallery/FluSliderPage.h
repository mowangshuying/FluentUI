#pragma once

#include "FluAEmptyPage.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluSlider.h"
#include "../Controls/FluVScrollView.h"

class FluSliderPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluSliderPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
