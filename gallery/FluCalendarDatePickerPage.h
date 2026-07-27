#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluCalendarDatePicker.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluVScrollView.h"

class FluCalendarDatePickerPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluCalendarDatePickerPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
