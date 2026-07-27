#pragma once

#include "../controls/FluWidget.h"
#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluPivot.h"

class FluPivotPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluPivotPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
