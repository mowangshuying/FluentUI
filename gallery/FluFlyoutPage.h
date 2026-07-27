#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluPushButton.h"
#include "../controls/FluConfirmFlyout.h"

class FluFlyoutPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluFlyoutPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
