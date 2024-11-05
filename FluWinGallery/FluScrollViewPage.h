#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluScrollArea.h"
#include "../FluControls/FluImageBox.h"

class FluScrollViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluScrollViewPage(QWidget* parent = nullptr);

  public:
    void onThemeChanged();
};
