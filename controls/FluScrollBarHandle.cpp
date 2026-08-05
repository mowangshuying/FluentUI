#include "FluScrollBarHandle.h"

FluScrollBarHandle::FluScrollBarHandle(Qt::Orientation orientation, QWidget* parent /*= nullptr*/) : QWidget(parent), m_orientation(orientation), m_thickness(3), m_isHovered(false)
{
    if (orientation == Qt::Vertical)
        setFixedWidth(3);
    else
        setFixedHeight(3);

    m_thicknessAnimation = new QPropertyAnimation(this, "thickness", this);
    m_thicknessAnimation->setDuration(150);
    m_thicknessAnimation->setEasingCurve(QEasingCurve::OutQuint);
}

QColor FluScrollBarHandle::getHandleHoverColor() const
{
    return m_handleHoverColor;
}

void FluScrollBarHandle::setHandleHoverColor(QColor color)
{
    m_handleHoverColor = color;
}

int FluScrollBarHandle::getThickness() const
{
    return m_thickness;
}

void FluScrollBarHandle::setThickness(int t)
{
    if (m_thickness == t)
        return;
    m_thickness = t;
    if (m_orientation == Qt::Vertical)
        setFixedWidth(t);
    else
        setFixedHeight(t);
    update();
}

void FluScrollBarHandle::setHovered(bool hovered)
{
    if (m_isHovered == hovered)
        return;
    m_isHovered = hovered;

    m_thicknessAnimation->stop();
    m_thicknessAnimation->setStartValue(m_thickness);
    m_thicknessAnimation->setEndValue(hovered ? 8 : 3);
    m_thicknessAnimation->start();
    update();
}

bool FluScrollBarHandle::isHovered() const
{
    return m_isHovered;
}

void FluScrollBarHandle::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    int r = 0;
    if (m_orientation == Qt::Vertical)
        r = width() / 2;
    else
        r = height() / 2;

    QColor color = m_isHovered ? m_handleHoverColor : m_handleBackgroundColor;
    painter.setBrush(QBrush(color.isValid() ? color : m_handleBackgroundColor));
    painter.drawRoundedRect(rect(), r, r);
}
