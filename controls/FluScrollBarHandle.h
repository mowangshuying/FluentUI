#pragma once

#include <QWidget>
#include <QPainter>
#include <QPropertyAnimation>
#include "../utils/FluUtils.h"

class FluScrollBarHandle : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int thickness READ getThickness WRITE setThickness)
    Q_PROPERTY(QColor handleHoverColor READ getHandleHoverColor WRITE setHandleHoverColor)
  public:
    FluScrollBarHandle(Qt::Orientation orientation, QWidget* parent = nullptr);

    void setHandleBackgroundColor(QColor color)
    {
        m_handleBackgroundColor = color;
        update();
    }

    QColor getHandleBackgroundColor()
    {
        return m_handleBackgroundColor;
    }

    QColor getHandleHoverColor() const;
    void setHandleHoverColor(QColor color);

    int getThickness() const;
    void setThickness(int t);

    void setHovered(bool hovered);
    bool isHovered() const;

    void paintEvent(QPaintEvent* event);

  protected:
    Qt::Orientation m_orientation;
    QColor m_handleBackgroundColor;
    QColor m_handleHoverColor;
    bool m_isHovered = false;
    int m_thickness = 3;
    QPropertyAnimation* m_thicknessAnimation;
};
