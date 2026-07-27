#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluScrollArea.h"
#include "../controls/FluImageBox.h"

class FluScrollViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluScrollViewPage(QWidget* parent = nullptr);

  public:
    void onThemeChanged();
};
