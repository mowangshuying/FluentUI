#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluCalendarDatePicker.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluVScrollView.h"

class FluCalendarDatePickerPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluCalendarDatePickerPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
