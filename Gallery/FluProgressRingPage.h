#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluProgressRing.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluDisplayBoxEx.h"
#include "../Controls/FluLabel.h"
#include "../Controls/FluComboBoxEx.h"
#include "../Controls/FluBusyProgressRing.h"

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
