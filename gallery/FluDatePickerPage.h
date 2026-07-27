#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDatePicker.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"

class FluDatePickerPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluDatePickerPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
