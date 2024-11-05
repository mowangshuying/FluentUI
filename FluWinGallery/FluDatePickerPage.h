#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDatePicker.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluDatePickerPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluDatePickerPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
