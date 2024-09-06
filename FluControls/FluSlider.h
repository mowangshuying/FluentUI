#pragma once

#include <QSlider>

#include "../FluUtils/FluUtils.h"

class FluSlider : public QSlider
{
    Q_OBJECT
  public:
    FluSlider(QWidget* parent = nullptr);

    FluSlider(Qt::Orientation orientation, QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
