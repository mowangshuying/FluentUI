#pragma once

#include "FluWidget.h"
#include <QPainter>
#include <QLinearGradient>
#include "../utils/FluUtils.h"
#include <QStyle>
#include <QStyleOption>
#include <QPainterPath>
#include <QPainter>
#include <QMouseEvent>
#include <QImage>

class FluColorViewGradient : public FluWidget
{
    Q_OBJECT
  public:
    FluColorViewGradient(QWidget* parent = nullptr);

    void setFixedSize(int w, int h);

    void setColor(QColor color);

    QColor getColor();

    bool findColor(QColor color, QPoint& point);

    bool isCloseTo(int target, int current, int radius);

    void circleMoveToPoint(QColor color);

    void mouseMoveEvent(QMouseEvent* event);

    void mousePressEvent(QMouseEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void colorChanged(QColor color);

  protected:
    QPixmap m_pixmap;

    // cached image of m_pixmap, used to avoid repeated toImage() in findColor.
    QImage m_image;

    QColor m_color;
    QPoint m_circleP;
    bool m_isPressed;
};
