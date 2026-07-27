#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluAppBarButton.h"

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
