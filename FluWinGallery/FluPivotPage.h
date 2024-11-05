#pragma once

#include "../FluControls/FluWidget.h"
#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluPivot.h"

class FluPivotPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluPivotPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
