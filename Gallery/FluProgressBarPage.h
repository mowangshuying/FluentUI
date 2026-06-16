#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluProgressBar.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"

class FluProgressBarPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluProgressBarPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
