#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluCheckBox.h"
#include "../controls/FluVScrollView.h"

class FluCheckBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluCheckBoxPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
