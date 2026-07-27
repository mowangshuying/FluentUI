#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluLabel.h"
#include "../controls/FluToggleButton.h"
#include "../controls/FluPushButton.h"
#include "../controls/FluVScrollView.h"

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
