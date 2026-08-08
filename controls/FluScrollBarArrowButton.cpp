#include "FluScrollBarArrowButton.h"

FluScrollBarArrowButton::FluScrollBarArrowButton(FluScrollBarArrowButtonType type /*= FluScrollBarArrowButtonType::ArrowUp*/, QWidget* parent /*= nullptr*/)
    : QPushButton(parent), m_normalColor(120, 120, 120), m_hoverColor(60, 60, 60), m_boundaryColor(200, 200, 200)
{
    m_aweSomeType = getIconTypeByArrowType(type);
    setFixedSize(12, 12);
    setAttribute(Qt::WA_Hover, true);
}

FluAwesomeTypeNameSpace::FluAwesomeType FluScrollBarArrowButton::getIconTypeByArrowType(FluScrollBarArrowButtonType type)
{
    switch (type)
    {
        case FluScrollBarArrowButtonType::ArrowUp:
            return FluAwesomeType::CaretSolidUp;
        case FluScrollBarArrowButtonType::ArrowDown:
            return FluAwesomeType::CaretSolidDown;
        case FluScrollBarArrowButtonType::ArrowLeft:
            return FluAwesomeType::CaretSolidLeft;
        case FluScrollBarArrowButtonType::ArrowRight:
            return FluAwesomeType::CaretSolidRight;
        default:
            return FluAwesomeType::CaretSolidUp;
    }

    return FluAwesomeType::CaretSolidUp;
}

void FluScrollBarArrowButton::setAtBoundary(bool atBoundary)
{
    if (m_isAtBoundary != atBoundary)
    {
        m_isAtBoundary = atBoundary;
        update();
    }
}

bool FluScrollBarArrowButton::isAtBoundary() const
{
    return m_isAtBoundary;
}

QColor FluScrollBarArrowButton::getNormalColor() const
{
    return m_normalColor;
}

void FluScrollBarArrowButton::setNormalColor(QColor color)
{
    m_normalColor = color;
    update();
}

QColor FluScrollBarArrowButton::getHoverColor() const
{
    return m_hoverColor;
}

void FluScrollBarArrowButton::setHoverColor(QColor color)
{
    m_hoverColor = color;
    update();
}

QColor FluScrollBarArrowButton::getBoundaryColor() const
{
    return m_boundaryColor;
}

void FluScrollBarArrowButton::setBoundaryColor(QColor color)
{
    m_boundaryColor = color;
    update();
}

void FluScrollBarArrowButton::enterEvent(QEnterEvent* event)
{
    QPushButton::enterEvent(event);
    m_isHovered = true;
    update();
}

void FluScrollBarArrowButton::leaveEvent(QEvent* event)
{
    QPushButton::leaveEvent(event);
    m_isHovered = false;
    update();
}

void FluScrollBarArrowButton::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);

    QColor iconColor;
    if (m_isAtBoundary)
        iconColor = m_boundaryColor;
    else if (m_isHovered)
        iconColor = m_hoverColor;
    else
        iconColor = m_normalColor;

    painter.drawPixmap(rect(), FluIconUtils::getFluentIconPixmap(m_aweSomeType, iconColor, rect().width(), rect().height()));
}
