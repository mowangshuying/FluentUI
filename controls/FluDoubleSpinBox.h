#pragma once

#include <QDoubleSpinBox>
#include "../utils/FluUtils.h"
#include <QContextMenuEvent>

class FluDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
  public:
    FluDoubleSpinBox(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

    bool eventFilter(QObject* watched, QEvent* event);

  protected:
    void onThemeChanged();
};
