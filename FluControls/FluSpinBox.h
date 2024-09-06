#pragma once

#include "../FluUtils/FluUtils.h"
#include <QSpinBox>

class FluSpinBox : public QSpinBox
{
    Q_OBJECT
  public:
    FluSpinBox(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();
};
