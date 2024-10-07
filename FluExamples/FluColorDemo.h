#pragma once

#include <QPainter>
#include "../FluControls/FluWidget.h"
#include "FluTemplateDemo.h"

class FluColorDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluColorDemo(QWidget *parent = nullptr);

    void setBgColor(const QColor &color);

  protected:
    void paintEvent(QPaintEvent *event);

  private:
    QColor m_bgColor;
};
