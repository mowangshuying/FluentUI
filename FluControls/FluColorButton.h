#pragma once

#include <QPushButton>
#include "../FluUtils/FluStyleSheetUitls.h"

class FluColorButton : public QPushButton
{
    Q_OBJECT
  public:
    FluColorButton(QColor backgroundColor, QWidget* parent = nullptr);

    QColor getBackgroundColor();

  protected:
    QColor m_backgroundColor;
};
