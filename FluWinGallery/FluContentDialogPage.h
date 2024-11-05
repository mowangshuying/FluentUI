#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluMessageBox.h"

class FluContentDialogPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluContentDialogPage(QWidget* parent = nullptr);
  public slots:
    void onThemeChanged();
};
