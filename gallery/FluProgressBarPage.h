#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluProgressBar.h"
#include "../utils/FluUtils.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"

class FluProgressBarPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluProgressBarPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
