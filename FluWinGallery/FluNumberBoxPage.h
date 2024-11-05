#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluSpinBox.h"
#include "../FluControls/FluDoubleSpinBox.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluNumberBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluNumberBoxPage(QWidget* parent = nullptr);

    void addSpinBox();

    void addDoubleSpinBox();

  public slots:
    void onThemeChanged();
};
