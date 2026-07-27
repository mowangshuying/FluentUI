#include "FluTimeLineIcon.h"

FluTimeLineIcon::FluTimeLineIcon(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setFixedSize(40, 40);
}

void FluTimeLineIcon::paintEvent(QPaintEvent* event)
{
    FluWidget::paintEvent(event);

    // Antialiasing.
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // draw line;
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(29, 29, 29));
    if (FluThemeUtils::isDarkTheme())
        painter.setBrush(QColor(229, 229, 229));
    painter.drawRect(QRectF(20 - 1.5, 0, 3, 14));

    // draw border;
    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(29, 29, 29));
    if (FluThemeUtils::isDarkTheme())
        painter.setBrush(QColor(229, 229, 229));
    painter.setPen(pen);

    QRectF outerBorderC(14, 14, 12, 12);
    painter.drawEllipse(outerBorderC);

    // draw outerC
    QRectF outerC(14, 14, 12, 12);
    pen.setWidth(4);
    pen.setColor(QColor(25, 106, 167));
    painter.setPen(pen);
    painter.setBrush(QColor(25, 106, 167));

    if (FluThemeUtils::isDarkTheme())
    {
        pen.setColor(QColor(118, 185, 237));
        painter.setPen(pen);
        painter.setBrush(QColor(118, 185, 237));
    }

    painter.drawEllipse(outerC);

    // draw innerC
    QRectF innerC(16, 16, 8, 8);
    pen.setColor(QColor(255, 255, 255));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.setBrush(QColor(255, 255, 255));

    if (FluThemeUtils::isDarkTheme())
    {
        pen.setColor(QColor(42, 42, 42));
        pen.setWidth(1);
        painter.setPen(pen);
        painter.setBrush(QColor(42, 42, 42));
    }

    painter.drawEllipse(innerC);

    // draw line;
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(29, 29, 29));
    if (FluThemeUtils::isDarkTheme())
        painter.setBrush(QColor(229, 229, 229));
    painter.drawRect(QRectF(20 - 1.5, 20 + 8, 3, 14));
}
