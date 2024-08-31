#pragma once

#include <QWidget>
#include <QPainter>
#include "../FluUtils/FluUtils.h"

class FluScrollBarHandle : public QWidget
{
    Q_OBJECT
  public:
    FluScrollBarHandle(Qt::Orientation orientation, QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

  protected:
    Qt::Orientation m_orientation;
};
