#pragma once

#include "FluAEmptyPage.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluPushButton.h"
#include "../Controls/FluMessageBox.h"

class FluContentDialogPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluContentDialogPage(QWidget* parent = nullptr);
  public slots:
    void onThemeChanged();
};
