#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluAppBarToggleButton.h"

class FluAppBarToggleButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluAppBarToggleButtonPage(QWidget* parent = nullptr);

    void addSymbolIconAppBarButton();

  public slots:
    void onThemeChanged();
};
