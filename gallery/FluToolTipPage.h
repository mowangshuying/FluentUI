#pragma once

#include "../controls/FluPushButton.h"
#include "../controls/FluToolTip.h"
#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"

class FluToolTipPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluToolTipPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
