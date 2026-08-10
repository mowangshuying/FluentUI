#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluComboBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluColorLabel.h"

class FluComboBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluComboBoxPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
