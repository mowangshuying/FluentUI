#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluAppBarButton.h"

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
