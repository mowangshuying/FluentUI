#pragma once

#include "FluAEmptyPage.h"
#include "../utils/FluUtils.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluPushButton.h"
#include "../controls/FluMessageBox.h"

class FluContentDialogPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluContentDialogPage(QWidget* parent = nullptr);
  public slots:
    void onThemeChanged();
};
