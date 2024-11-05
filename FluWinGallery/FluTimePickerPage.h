#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluTimePicker24H.h"
#include "../FluControls/FluTimePickerAP.h"

class FluTimePickerPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluTimePickerPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
