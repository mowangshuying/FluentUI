#pragma once

#include "FluAEmptyPage.h"
#include "../utils/FluUtils.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluTextEdit.h"
#include "../controls/FluVScrollView.h"

class FluTextBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluTextBoxPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
