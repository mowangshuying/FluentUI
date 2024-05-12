#pragma once

#include <QPainter>
#include "../FluControls/FluWidget.h"

class FluColorDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluColorDemo(QWidget *parent = nullptr) : FluWidget(parent)
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
