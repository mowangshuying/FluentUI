#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluProgressRing.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluDisplayBoxEx.h"
#include "../FluControls/FluLabel.h"
#include "../FluControls/FluComboBoxEx.h"
#include "../FluControls/FluBusyProgressRing.h"

class FluProgressRingPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluProgressRingPage(QWidget* parent = nullptr);

    void addIndeterminateProgressRing();

    void addIndeterminateRing();

    void addBusyRing();

  public slots:
    void onThemeChanged();

  protected:
    int m_nTimes;
};
