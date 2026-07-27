#pragma once

#include "FluAEmptyPage.h"
#include "../utils/FluUtils.h"
#include "../controls/FluDropDownButton.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"

class FluDropDownButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluDropDownButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
