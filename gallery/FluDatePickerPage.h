#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDatePicker.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"

class FluDatePickerPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluDatePickerPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
