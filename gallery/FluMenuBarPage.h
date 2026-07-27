#pragma once

#include "FluAEmptyPage.h"
#include "../utils/FluUtils.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluMenu.h"
#include "../controls/FluMenuBar.h"
#include "../controls/FluVScrollView.h"

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
