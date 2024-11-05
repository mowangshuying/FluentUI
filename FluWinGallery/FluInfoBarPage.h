#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluShortInfoBar.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluDisplayBoxEx.h"
#include "../FluControls/FluComboBoxEx.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluInfoBarMgr.h"
#include "../FluControls/FluLabel.h"
#include "../FluControls/FluCheckBox.h"

class FluInfoBarPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluInfoBarPage(QWidget* parent = nullptr);

    void addClosableInfoBar();

    void addDynamicInfoBar();
  public slots:
    void onThemeChanged();
};
