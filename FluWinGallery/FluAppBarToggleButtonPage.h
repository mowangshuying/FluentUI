#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluAppBarToggleButton.h"

class FluAppBarToggleButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluAppBarToggleButtonPage(QWidget* parent = nullptr);

    void addSymbolIconAppBarButton();

  public slots:
    void onThemeChanged();
};
