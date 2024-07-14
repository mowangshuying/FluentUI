#pragma once

#include <QPainter>
#include <QPainterPath>
#include "FluWidget.h"

class FluColorViewHHandle : public FluWidget
{
    Q_OBJECT
  public:
      FluColorViewHHandle(QWidget* parent = nullptr) : FluWidget(parent)
      {

      }

      void setFixedSize(int w, int h)
      {
          FluWidget::setFixedSize(w, h);
          update();
      }

      void setColor(QColor color)
      {
          m_color = color;
          update();
      }

      QColor getColor()
      {
          return m_color;
      }

      void paintEvent(QPaintEvent* event)
      {
          QPainter painter(this);
          painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
          
          // draw handle;
          painter.setPen(Qt::NoPen);
          painter.setBrush(m_color);
          painter.drawRoundedRect(rect(), 6, 6);
      }
  protected:
      QColor m_color;
};
