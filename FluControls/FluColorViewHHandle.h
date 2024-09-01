#pragma once

#include <QPainter>
#include <QPainterPath>
#include "FluWidget.h"
#include <QMouseEvent>
#include "../FluUtils/FluUtils.h"
#include <QLinearGradient>

class FluColorViewHHandle : public FluWidget
{
    Q_OBJECT
  public:
    FluColorViewHHandle(QWidget* parent = nullptr);

    void setMaxV(int nV);

    int getMaxV();

    void setMinV(int nV);

    int getMinV();

    float getV();

    void setV(float v);

    void updateVByMouseOper(int nX, bool bEmitSignal = true);

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

    int m_nMaxV;
    int m_nMinV;
    float m_fV;

    bool m_bPressed;
};
