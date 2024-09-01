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
