#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluShortInfoBar.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluDisplayBoxEx.h"
#include "../Controls/FluComboBoxEx.h"
#include "../Controls/FluPushButton.h"
#include "../Controls/FluInfoBarMgr.h"
#include "../Controls/FluLabel.h"
#include "../Controls/FluCheckBox.h"

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
