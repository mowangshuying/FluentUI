#pragma once

#include "../FluUtils/FluUtils.h"
#include <QPushButton>

class FluStyleButton : public QPushButton
{
    Q_OBJECT
  public:
      FluStyleButton(QWidget* parent = nullptr) : QPushButton(parent)
      {
          setFixedSize(200, 30);
          QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluStyleButton.qss");
          setStyleSheet(qss);
      }
};
