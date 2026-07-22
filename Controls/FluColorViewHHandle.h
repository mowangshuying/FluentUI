#pragma once

#include <QPainter>
#include <QPainterPath>
#include "FluWidget.h"
#include <QMouseEvent>
#include "../Utils/FluUtils.h"
#include <QLinearGradient>

class FluColorViewHHandle : public FluWidget
{
    Q_OBJECT
  public:
    FluColorViewHHandle(QWidget* parent = nullptr);

    void setMaxValue(int value);

    int getMaxValue();

    void setMinValue(int value);

    int getMinValue();

    float getValue();

    void setValue(float value);

    void updateValueByMouseOperation(int xPosition, bool shouldEmitSignal = true);

    void setFixedSize(int w, int h);

    void setColor(QColor color, bool bEmitSignal = true);

    QColor getColor();

    void mouseMoveEvent(QMouseEvent* event);

    void mousePressEvent(QMouseEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);

  signals:
    void colorChanged(QColor color);
    void valueChanged(float percentage);
    void pressed();

  protected:
    QColor m_color;
    QPoint m_circleP;

    int m_maxValue;
    int m_minValue;
    float m_value;

    bool m_isPressed;
};
