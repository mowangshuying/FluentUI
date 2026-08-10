#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluDisplayBoxEx.h"
#include "../controls/FluComboBoxEx.h"
#include "../controls/FluPushButton.h"
#include "../controls/FluInfoBarMgr.h"
#include "../controls/FluLabel.h"
#include "../controls/FluCheckBox.h"
#include "../controls/FluInfoBar.h"

class FluInfoBarPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluInfoBarPage(QWidget* parent = nullptr);

    void addPersistentInfoBar();

    void addClosableInfoBar();

    void addDynamicInfoBar();

    void addBottomRightInfoBar();
  public slots:
    void onThemeChanged();

  protected:
    FluInfoBar* m_infoBar;
};
