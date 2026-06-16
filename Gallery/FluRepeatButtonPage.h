#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluRepeatButton.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluVScrollView.h"

class FluRepeatButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRepeatButtonPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
