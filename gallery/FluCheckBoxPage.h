#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluCheckBox.h"
#include "../Controls/FluVScrollView.h"

class FluCheckBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluCheckBoxPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
