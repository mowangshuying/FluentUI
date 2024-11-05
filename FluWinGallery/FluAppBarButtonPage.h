#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluAppBarButton.h"

class FluAppBarButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluAppBarButtonPage(QWidget* parent = nullptr);

    void addSymbolIconAppBarButton();

    void addKeyboardAcceleratorAppBarButton();

  public slots:
    void onThemeChanged();
};
