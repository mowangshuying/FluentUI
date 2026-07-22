#include "FluScrollBarHandle.h"

FluScrollBarHandle::FluScrollBarHandle(Qt::Orientation orientation, QWidget* parent /*= nullptr*/) : QWidget(parent), m_orientation(orientation)
{
    if (orientation == Qt::Vertical)
        setFixedWidth(3);
    else
        setFixedHeight(3);
}

void FluScrollBarHandle::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    // LOG_DEBUG << "Rect:" << rect();
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    //
    int r = 0;
    if (m_orientation == Qt::Vertical)
    {
        r = width() / 2;
    }
    else
    {
        r = height() / 2;
    }

    // QColor color;

    painter.setBrush(QBrush(m_handleBackgroundColor));
    painter.drawRoundedRect(rect(), r, r);
}
