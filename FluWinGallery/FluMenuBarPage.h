#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluMenu.h"
#include "../FluControls/FluMenuBar.h"
#include "../FluControls/FluVScrollView.h"

class FluMenuBarPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluMenuBarPage(QWidget* parent = nullptr);

    void addSimpleMenuBar();

    void addMenuBarWithAccelerators();

  public slots:
    void onThemeChanged();

  protected:
};
