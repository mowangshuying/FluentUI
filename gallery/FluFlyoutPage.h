#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluPushButton.h"
#include "../Controls/FluConfirmFlyout.h"

class FluFlyoutPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluFlyoutPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
