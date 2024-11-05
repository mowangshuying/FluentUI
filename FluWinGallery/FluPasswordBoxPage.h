#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluPasswordBox.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluPasswordBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluPasswordBoxPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
