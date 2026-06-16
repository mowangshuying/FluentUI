#pragma once

#include "FluAEmptyPage.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluDropDownButton.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"

class FluDropDownButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluDropDownButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
