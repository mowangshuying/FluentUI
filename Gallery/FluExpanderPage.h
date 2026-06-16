#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluLabel.h"
#include "../Controls/FluToggleButton.h"
#include "../Controls/FluPushButton.h"
#include "../Controls/FluVScrollView.h"

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
