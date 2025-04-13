#pragma once

#include <QWidget>
#include <QPainter>
#include "../FluUtils/FluUtils.h"

class FluScrollBarHandle : public QWidget
{
    Q_OBJECT
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

    void paintEvent(QPaintEvent* event);

  protected:
    Qt::Orientation m_orientation;
    QColor m_handleBackgroundColor;
};
