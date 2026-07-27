#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluHFlipView.h"
#include "../Controls/FluVFlipView.h"
#include "../Controls/FluVScrollView.h"

class FluFlipViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluFlipViewPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
