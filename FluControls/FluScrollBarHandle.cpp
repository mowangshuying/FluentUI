#include "FluScrollbarHandle.h"

FluScrollbarHandle::FluScrollbarHandle(Qt::Orientation orientation, QWidget* parent /*= nullptr*/) : QWidget(parent), m_orientation(orientation)
{
    if (orientation == Qt::Vertical)
        setFixedWidth(3);
    else
        setFixedHeight(3);
}

void FluScrollbarHandle::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    // LOG_DEBUG << "Rect:" << rect();
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    //
    int nR = 0;
    if (m_orientation == Qt::Vertical)
    {
        nR = width() / 2;
    }
    else
    {
        nR = height() / 2;
    }

    QColor color;
    if (FluThemeUtils::isLightTheme())
    {
        color = QColor(138, 138, 138);
    }
    else if (FluThemeUtils::isDarkTheme())
    {
        color = QColor(159, 159, 159);
    }

    painter.setBrush(QBrush(color));
    painter.drawRoundedRect(rect(), nR, nR);
}
