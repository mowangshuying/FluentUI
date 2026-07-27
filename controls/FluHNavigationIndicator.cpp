#include "FluHNavigationIndicator.h"

FluHNavigationIndicator::FluHNavigationIndicator(QWidget *parent /*= nullptr*/)
    : QWidget(parent), m_selected(false), m_indicatorWidth(0)
{
    setFixedHeight(3);
    m_widthAnimation = new QPropertyAnimation(this, "indicatorWidth", this);
    m_widthAnimation->setDuration(200);
    m_widthAnimation->setEasingCurve(QEasingCurve::OutCubic);
}

bool FluHNavigationIndicator::isSelected() const
{
    return m_selected;
}

void FluHNavigationIndicator::setSelected(bool b)
{
    m_selected = b;
    update();
}

int FluHNavigationIndicator::indicatorWidth() const
{
    return m_indicatorWidth;
}

void FluHNavigationIndicator::setIndicatorWidth(int w)
{
    m_indicatorWidth = w;
    update();
}

void FluHNavigationIndicator::animateSelect(bool selected)
{
    m_selected = selected;
    m_widthAnimation->stop();
    if (selected)
    {
        m_widthAnimation->setStartValue(0);
        m_widthAnimation->setEndValue(width());
        m_widthAnimation->start();
    }
    else
    {
        m_widthAnimation->setStartValue(m_indicatorWidth);
        m_widthAnimation->setEndValue(0);
        m_widthAnimation->start();
    }
}

void FluHNavigationIndicator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if (!m_selected || m_indicatorWidth <= 0)
    {
        painter.fillRect(rect(), Qt::transparent);
        return;
    }

    QColor indicatorColor;
    if (FluThemeUtils::isLightTheme())
        indicatorColor = QColor(0, 90, 158);
    else if (FluThemeUtils::isDarkTheme())
        indicatorColor = QColor(118, 185, 237);
    else
        indicatorColor = QColor(82, 139, 255);

    painter.setBrush(indicatorColor);
    painter.setPen(Qt::NoPen);

    int centerX = (width() - m_indicatorWidth) / 2;
    QRect r(centerX, 0, m_indicatorWidth, height());
    painter.drawRoundedRect(r.adjusted(0, 0, 0, 0), 1.5, 1.5);
}
