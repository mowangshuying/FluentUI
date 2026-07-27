#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluCalendarDatePicker.h"
#include "../utils/FluUtils.h"
#include "../controls/FluVScrollView.h"

class FluCalendarDatePickerPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluCalendarDatePickerPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
