#pragma once

#include "FluAEmptyPage.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluSpinBox.h"
#include "../Controls/FluDoubleSpinBox.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"

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
