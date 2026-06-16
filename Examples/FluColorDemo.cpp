#include "FluColorDemo.h"

FluColorDemo::FluColorDemo(QWidget *parent /*= nullptr*/) : FluTemplateDemo(parent)
{
}

void FluColorDemo::setBgColor(const QColor &color)
{
    m_bgColor = color;
    update();
}

void FluColorDemo::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(rect(), m_bgColor);
}
