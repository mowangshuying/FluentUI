#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluProgressBar.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluProgressBarPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluProgressBarPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
