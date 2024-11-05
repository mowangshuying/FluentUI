#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluHFlipView.h"
#include "../FluControls/FluVFlipView.h"
#include "../FluControls/FluVScrollView.h"

class FluFlipViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluFlipViewPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
