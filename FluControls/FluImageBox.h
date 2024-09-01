#pragma once

#include "FluWidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>

class FluImageBox : public FluWidget
{
    Q_OBJECT
  public:
    FluImageBox(QWidget* parent = nullptr);

    FluImageBox(QPixmap pixmap, QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

  protected:
    QPixmap m_pixmap;
};
