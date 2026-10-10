#pragma once

#include "../utils/FluUtils.h"
#include <QSpinBox>
#include <QContextMenuEvent>

class FluSpinBox : public QSpinBox
{
    Q_OBJECT
  public:
    FluSpinBox(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

    bool eventFilter(QObject* watched, QEvent* event);

  protected:
    void onThemeChanged();
};
