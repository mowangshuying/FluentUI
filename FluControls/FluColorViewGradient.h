#pragma once

#include "FluWidget.h"
#include <QPainter>
#include <QLinearGradient>
#include "../FluUtils/FluUtils.h"
#include <QStyle>
#include <QStyleOption>
#include <QPainterPath>

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

      void paintEvent(QPaintEvent* event)
      {
          QPainter painter(this);
          
          // clip;
          QPainterPath path;
          path.addRoundedRect(rect(), 4, 4);
          painter.setClipPath(path);

          // pixmap;
          painter.drawPixmap(rect(), m_pixmap);

      }

  protected:
      QPixmap m_pixmap;
};
