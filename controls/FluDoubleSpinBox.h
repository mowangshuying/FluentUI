#pragma once

#include <QDoubleSpinBox>
#include "../utils/FluUtils.h"

class FluDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
  public:
    FluDoubleSpinBox(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

  protected:
    void onThemeChanged();
};
