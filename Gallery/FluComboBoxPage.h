#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluComboBoxEx.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluColorLabel.h"

class FluComboBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluComboBoxPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
