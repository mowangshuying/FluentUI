#pragma once

#include <QPainter>
#include "../FluControls/FluWidget.h"
#include "FluTemplateDemo.h"

class FluColorDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluColorDemo(QWidget *parent = nullptr) : FluTemplateDemo(parent)
    {
    }

    void setBgColor(const QColor &color)
    {
        m_bgColor = color;
        update();
    }

  protected:
    void paintEvent(QPaintEvent *event)
    {
        QWidget::paintEvent(event);
        QPainter painter(this);
        painter.fillRect(rect(), m_bgColor);
    }

  private:
    QColor m_bgColor;
};
