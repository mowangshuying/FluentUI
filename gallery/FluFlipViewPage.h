#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluHFlipView.h"
#include "../controls/FluVFlipView.h"
#include "../controls/FluVScrollView.h"

class FluFlipViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluFlipViewPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
