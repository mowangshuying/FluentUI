#pragma once

#include "FluWidget.h"
#include <QPainter>
#include <QLinearGradient>
#include "../FluUtils/FluUtils.h"
#include <QStyle>
#include <QStyleOption>
#include <QPainterPath>
#include <QPainter>
#include <QMouseEvent>

class FluColorViewGradient : public FluWidget
{
    Q_OBJECT
  public:
    FluColorViewGradient(QWidget* parent = nullptr);

    void setFixedSize(int w, int h);

    void setColor(QColor color);

    QColor getColor();

    bool findColor(QColor color, QPoint& point);

    bool atRange(int i, int j, int nRadius);

    void circleMoveToPoint(QColor color);

    void mouseMoveEvent(QMouseEvent* event);

    void mousePressEvent(QMouseEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void colorChanged(QColor color);

  protected:
    QPixmap m_pixmap;

    QColor m_color;
    QPoint m_circleP;
    bool m_bPressed;
};
