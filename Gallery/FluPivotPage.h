#pragma once

#include "../Controls/FluWidget.h"
#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluPivot.h"

class FluPivotPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluPivotPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
