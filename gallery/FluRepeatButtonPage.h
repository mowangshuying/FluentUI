#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluRepeatButton.h"
#include "../utils/FluUtils.h"
#include "../controls/FluVScrollView.h"

class FluRepeatButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRepeatButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
