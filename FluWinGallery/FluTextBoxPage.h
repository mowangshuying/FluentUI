#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluTextEdit.h"
#include "../FluControls/FluVScrollView.h"

class FluTextBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluTextBoxPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
