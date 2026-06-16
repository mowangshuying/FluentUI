#pragma once

#include "FluAEmptyPage.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluTextEdit.h"
#include "../Controls/FluVScrollView.h"

class FluTextBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluTextBoxPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
