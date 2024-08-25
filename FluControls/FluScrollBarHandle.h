#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QPainter>

class FluScrollBarHandle : public QWidget
{
  public:
      FluScrollBarHandle(Qt::Orientation orientation = Qt::Orientation::Vertical, QWidget* parent = nullptr)
      {

      }

      void initVertical(Qt::Orientation orientation)
      {
          if (orientation != Qt::Orientation::Vertical)
              return;

          setFixedWidth(12);

      }

      void initHorizontal(Qt::Orientation orientation)
      {
          if (orientation != Qt::Orientation::Horizontal)
              return;
          setFixedWidth(12);
      }
      
      void setHandleBackgoundColor(QColor color)
      {
          m_handleBackgoundColor = color;
      }

      QColor getHandleBackgoundColor()
      {
          return m_handleBackgoundColor;
      }

      void drawHandleBackground(QPainter *painter)
      {
          painter->setBrush(m_handleBackgoundColor);
          painter->drawRoundedRect(rect(), 6, 6);
      }

      void paintEvent(QPaintEvent* event)
      {
          QPainter painter(this);
          painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
          painter.setPen(Qt::NoPen);
      }
  protected:
      QColor m_handleBackgoundColor;

};
