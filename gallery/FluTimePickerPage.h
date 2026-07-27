#pragma once

#include "FluAEmptyPage.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluTimePicker24H.h"
#include "../Controls/FluTimePickerAP.h"

class FluTimePickerPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluTimePickerPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
