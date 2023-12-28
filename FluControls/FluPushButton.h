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
        QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/FluPushButton.qss");
        setStyleSheet(qss);
    }

  protected:
};