#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluCheckBox.h"
#include "../FluControls/FluVScrollView.h"

class FluCheckBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluCheckBoxPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
