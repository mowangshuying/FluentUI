#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluScrollArea.h"
#include "../Controls/FluImageBox.h"

class FluScrollViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluScrollViewPage(QWidget* parent = nullptr);

  public:
    void onThemeChanged();
};
