#pragma once

#include "FluWidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

class FluTimeLineIcon : public FluWidget
{
    Q_OBJECT
  public:
    FluTimeLineIcon(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);
};
