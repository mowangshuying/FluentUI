#pragma once

#include <QPainter>
#include "FluWidget.h"
#include <QPainter>
#include <QPainterPath>

class FluColorViewVHandle : public FluWidget
{
    Q_OBJECT
  public:
    FluColorViewVHandle(QWidget* parent = nullptr) : FluWidget(parent)
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

        // clip;
        QPainterPath path;
        path.addRoundedRect(rect(), 4, 4);
        painter.setClipPath(path);

        // color;
        painter.setPen(Qt::NoPen);
        painter.setBrush(m_color);

        painter.drawRect(rect());
    }

  protected:
    QColor m_color;
};
