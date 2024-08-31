#pragma once

#include <QWidget>
#include <QPainter>
#include "../FluUtils/FluUtils.h"

class FluScrollbarHandle : public QWidget
{
    Q_OBJECT
  public:
    FluScrollbarHandle(Qt::Orientation orientation, QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

  protected:
    Qt::Orientation m_orientation;
};
