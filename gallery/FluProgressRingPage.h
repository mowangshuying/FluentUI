#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluProgressRing.h"
#include "../utils/FluUtils.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluDisplayBoxEx.h"
#include "../controls/FluLabel.h"
#include "../controls/FluComboBoxEx.h"
#include "../controls/FluBusyProgressRing.h"

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
    int m_times;
};
