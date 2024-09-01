#include "FluImageBox.h"

FluImageBox::FluImageBox(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_pixmap = QPixmap();
}

FluImageBox::FluImageBox(QPixmap pixmap, QWidget* parent /*= nullptr*/) : FluImageBox(parent)
{
    m_pixmap = pixmap;
}

void FluImageBox::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    // draw a round pixmap
    QPainter painter(this);
    QPainterPath path;
    path.addRoundedRect(rect(), 4, 4);
    painter.setClipPath(path);

    m_pixmap = m_pixmap.scaled(rect().width(), rect().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(rect(), m_pixmap);
}
