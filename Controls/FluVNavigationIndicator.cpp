#include "FluVNavigationIndicator.h"

FluVNavigationIndicator::FluVNavigationIndicator(QWidget *parent /*= nullptr*/) : QWidget(parent), m_selected(false)
{
    setFixedSize(3, 16);
}

bool FluVNavigationIndicator::isSelected() const
{
    return m_selected;
}

void FluVNavigationIndicator::setSelected(bool b)
{
    m_selected = b;
    update();
}

void FluVNavigationIndicator::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if (m_selected)
    {
        if (FluThemeUtils::isLightTheme())
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(0, 90, 158));
        }
        else if (FluThemeUtils::isDarkTheme())
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(118, 185, 237));
        }
        else
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(82, 139, 255));
        }
    }
    else
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::transparent);
    }
    painter.drawRoundedRect(rect(), 1.5, 1.5);
}
