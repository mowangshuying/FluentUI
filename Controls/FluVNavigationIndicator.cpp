#include "FluVNavigationIndicator.h"

FluVNavigationIndicator::FluVNavigationIndicator(QWidget *parent /*= nullptr*/) : QWidget(parent), m_selected(false), m_indicatorHeight(0), m_targetHeight(0)
{
    setFixedWidth(3);
    setMinimumHeight(0);
    setMaximumHeight(16);
    m_heightAnimation = new QPropertyAnimation(this, "indicatorHeight", this);
    m_heightAnimation->setDuration(200);
}

bool FluVNavigationIndicator::isSelected() const
{
    return m_selected;
}

void FluVNavigationIndicator::setSelected(bool b)
{
    if (m_selected == b)
        return;
    m_selected = b;
    m_heightAnimation->stop();
    m_heightAnimation->setStartValue(m_indicatorHeight);
    m_heightAnimation->setEndValue(b ? 16 : 0);
    m_heightAnimation->start();
}

int FluVNavigationIndicator::indicatorHeight() const
{
    return m_indicatorHeight;
}

void FluVNavigationIndicator::setIndicatorHeight(int h)
{
    m_indicatorHeight = h;
    setFixedHeight(h);
}

void FluVNavigationIndicator::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if (m_indicatorHeight == 0)
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor color;
    if (FluThemeUtils::isLightTheme())
        color = QColor(0, 90, 158);
    else if (FluThemeUtils::isDarkTheme())
        color = QColor(118, 185, 237);
    else
        color = QColor(82, 139, 255);

    painter.setPen(Qt::NoPen);
    painter.setBrush(color);

    qreal radius = width() * 1.0 / 2;
    QRect r = rect();
    r.setTop((16 - m_indicatorHeight) / 2);
    r.setHeight(m_indicatorHeight);
    painter.drawRoundedRect(r, radius, radius);
}
