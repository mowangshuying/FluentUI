#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluComboBoxEx.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluColorLabel.h"

class FluComboBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluComboBoxPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
