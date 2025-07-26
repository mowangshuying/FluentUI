#pragma once

#include "FluRoundMenu.h"
#include "FluIndicatorMenuItemDeleage.h"
#include "../FluUtils/FluUtils.h"

class FluIndicatorRoundMenu : public FluRoundMenu
{
    Q_OBJECT
  public:
    FluIndicatorRoundMenu(QWidget* parent = nullptr);

    FluIndicatorRoundMenu(QString title, FluAwesomeType iconType, QWidget* parent = nullptr);

    void popup(QPoint pos);
};
