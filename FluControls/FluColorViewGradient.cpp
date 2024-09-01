#include "FluColorViewGradient.h"

FluColorViewGradient::FluColorViewGradient(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setFixedSize(192, 192);
    m_pixmap = QPixmap("../res/ControlResImages/GradientColor.png");
    m_pixmap = m_pixmap.scaled(192, 192);
}

void FluColorViewGradient::setFixedSize(int w, int h)
{
    FluWidget::setFixedSize(w, h);
    m_pixmap = m_pixmap.scaled(w, h);
    update();
}

void FluColorViewGradient::setColor(QColor color)
{
    m_color = color;
}

QColor FluColorViewGradient::getColor()
{
    return m_color;
}
