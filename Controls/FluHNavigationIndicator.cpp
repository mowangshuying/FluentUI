#include "FluHNavigationIndicator.h"

FluHNavigationIndicator::FluHNavigationIndicator(QWidget *parent /*= nullptr*/) : QWidget(parent), m_selected(false)
{
    setFixedHeight(3);
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

void FluHNavigationIndicator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if (!m_selected)
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
    painter.drawRoundedRect(rect().adjusted(4, 0, -4, 0), 1.5, 1.5);
}
