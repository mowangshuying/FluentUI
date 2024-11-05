#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluLabel.h"
#include "../FluControls/FluToggleButton.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluVScrollView.h"

class FluExpanderPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluExpanderPage(QWidget* parent = nullptr);

    void addExpanderDemo1();

    void addExpanderDemo2();

    void addExpanderDemo3();

  public slots:
    void onThemeChanged();
};
