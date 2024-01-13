#pragma once

#include "../FluUtils/FluUtils.h"
#include "FluDef.h"
#include <QPushButton>

class FluGraphicalButton : public QPushButton
{
    Q_OBJECT
  public:
      FluGraphicalButton(QWidget* parent = nullptr) : QPushButton(parent)
      {
          setFixedSize(50, 50);
          setIconSize(QSize(28,28));
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluGraphicalButton.qss", this);
      }
};
