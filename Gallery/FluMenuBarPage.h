#pragma once

#include "FluAEmptyPage.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluMenu.h"
#include "../Controls/FluMenuBar.h"
#include "../Controls/FluVScrollView.h"

class FluMenuBarPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluMenuBarPage(QWidget* parent = nullptr);

    void addSimpleMenuBar();

    void addMenuBarWithAccelerators();

    void addRoundMenu();

  public slots:
    void onThemeChanged();

  protected:
};
