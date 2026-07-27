#pragma once

#include "FluAEmptyPage.h"
#include "../utils/FluUtils.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluTimePicker24H.h"
#include "../controls/FluTimePickerAP.h"

class FluTimePickerPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluTimePickerPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
