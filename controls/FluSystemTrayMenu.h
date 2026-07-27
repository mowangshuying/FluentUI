#pragma once

#include "FluRoundMenu.h"

class FluSystemTrayMenu : public FluRoundMenu
{
  public:
    FluSystemTrayMenu(QWidget* parent = nullptr) : FluRoundMenu(parent)
    {
    }

    FluSystemTrayMenu(QString title, FluAwesomeType iconType = FluAwesomeType::None, QWidget* parent = nullptr) : FluRoundMenu(title, iconType, parent)
    {
    }

  public:
    QSize sizeHint()
    {
        auto margins = layout()->contentsMargins();
        auto sizeH = layout()->sizeHint();

        return QSize(sizeH.width() - margins.right(), sizeH.height() - margins.bottom());
    }
};
