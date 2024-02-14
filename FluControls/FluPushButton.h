#pragma once

#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>

#include "../FluUtils/FluStyleSheetUitls.h"

class FluPushButton : public QPushButton
{
    Q_OBJECT
  public:
    FluPushButton(QWidget *parent = nullptr) : QPushButton(parent)
    {
        setFixedSize(200, 30);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPushButton.qss", this);
    }

  protected:
};