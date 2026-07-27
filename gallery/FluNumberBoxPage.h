#pragma once

#include "FluAEmptyPage.h"
#include "../utils/FluUtils.h"
#include "../controls/FluSpinBox.h"
#include "../controls/FluDoubleSpinBox.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"

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
