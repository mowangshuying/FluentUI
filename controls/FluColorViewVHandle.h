#pragma once

#include <QPainter>
#include "FluWidget.h"
#include <QPainter>
#include <QPainterPath>

class FluColorViewVHandle : public FluWidget
{
    Q_OBJECT
  public:
    FluColorViewVHandle(QWidget* parent = nullptr);

    void setFixedSize(int w, int h);

    void setColor(QColor color);

    QColor getColor();

    void paintEvent(QPaintEvent* event);

  protected:
    QColor m_color;
};
