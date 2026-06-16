#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluAppBarToggleButton.h"

class FluAppBarToggleButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluAppBarToggleButtonPage(QWidget* parent = nullptr);

    void addSymbolIconAppBarButton();

  public slots:
    void onThemeChanged();
};
