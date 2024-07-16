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
      FluColorViewGradient(QWidget* parent = nullptr) : FluWidget(parent)
      {
          setFixedSize(192, 192);
          m_pixmap = QPixmap("../res/ControlResImages/GradientColor.png");
          m_pixmap = m_pixmap.scaled(192, 192);
      }

      void setFixedSize(int w, int h)
      {
          FluWidget::setFixedSize(w, h);
          m_pixmap = m_pixmap.scaled(w, h);
          update();
      }

      void setColor(QColor color)
      {
          m_color = color;
      }

      QColor getColor()
      {
          return m_color;
      }

      void mouseMoveEvent(QMouseEvent* event)
      {
          if (m_bPressed)
          {
              m_circleP = QPoint(event->pos().x(), event->pos().y());
              if (event->pos().x() < 8)
              {
                  m_circleP.setX(8);
              }
              else if (event->pos().x() > rect().width() - 8)
              {
                  m_circleP.setX(rect().width() - 8);
              }

              if (event->pos().y() < 8)
              {
                  m_circleP.setY(8);
              }
              else if (event->pos().y() > rect().height() - 8)
              {
                  m_circleP.setY(rect().height() - 8);
              }

              m_bPressed = true;
              m_color = m_pixmap.toImage().pixelColor(m_circleP);
              colorChanged(m_color);
              update();
          }
      }

      void mousePressEvent(QMouseEvent* event)
      {
          m_circleP = QPoint(event->pos().x(), event->pos().y());
          if (event->pos().x() < 8)
          {
              m_circleP.setX(8);
          }
          else if (event->pos().x() > rect().width() - 8)
          {
              m_circleP.setX(rect().width() - 8);
          }

          if (event->pos().y() < 8)
          {
              m_circleP.setY(8);
          }
          else if (event->pos().y() > rect().height() - 8)
          {
              m_circleP.setY(rect().height() - 8);
          }

          m_bPressed = true;
          m_color = m_pixmap.toImage().pixelColor(m_circleP);
#ifdef _DEBUG
          LOG_DEBUG << "color r:" << m_color.red();
          LOG_DEBUG << "color g:" << m_color.green();
          LOG_DEBUG << "color b:" << m_color.blue();
#endif
          colorChanged(m_color);
          update();
      }

      void mouseReleaseEvent(QMouseEvent* event)
      {
          m_bPressed = false;
      }

      void paintEvent(QPaintEvent* event)
      {
          QPainter painter(this);
          painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
          
          // clip;
          QPainterPath path;
          path.addRoundedRect(rect(), 4, 4);
          painter.setClipPath(path);

          // pixmap;
          painter.drawPixmap(rect(), m_pixmap);

          // draw circle;
          QPen pen;
          pen.setWidth(3);
          pen.setColor(Qt::black);
          painter.setPen(pen);
          painter.drawEllipse(m_circleP, 6, 6);
      }
signals:
      void colorChanged(QColor color);
  protected:
      QPixmap m_pixmap;

      QColor m_color;
      QPoint m_circleP;
      bool m_bPressed;
};
