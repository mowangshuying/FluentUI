#pragma once

#include "FluWidget.h"
#include <QStyleOption>
#include <QPainter>
#include "../FluUtils/FluUtils.h"

class FluHSplitLine : public FluWidget
{
    Q_OBJECT
  public:
    FluHSplitLine(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

  public slots:
    void onThemeChanged();
};
