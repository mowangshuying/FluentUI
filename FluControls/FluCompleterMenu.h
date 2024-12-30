#pragma once

#include "FluRoundMenu.h"

class FluCompleterMenu : public FluRoundMenu
{
    Q_OBJECT
  public:
    FluCompleterMenu(QWidget* parent = nullptr);
    FluCompleterMenu(QString title, FluAwesomeType iconType, QWidget* parent = nullptr);
};
