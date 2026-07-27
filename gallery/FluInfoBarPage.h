#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluShortInfoBar.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluDisplayBoxEx.h"
#include "../controls/FluComboBoxEx.h"
#include "../controls/FluPushButton.h"
#include "../controls/FluInfoBarMgr.h"
#include "../controls/FluLabel.h"
#include "../controls/FluCheckBox.h"

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
