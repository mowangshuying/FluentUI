#include "FluColorViewVHandle.h"

FluColorViewVHandle::FluColorViewVHandle(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
}

void FluColorViewVHandle::setFixedSize(int w, int h)
{
    FluWidget::setFixedSize(w, h);
    update();
}

void FluColorViewVHandle::setColor(QColor color)
{
    m_color = color;
    update();
}

QColor FluColorViewVHandle::getColor()
{
    return m_color;
}

void FluColorViewVHandle::paintEvent(QPaintEvent* event)
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
