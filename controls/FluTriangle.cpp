#include "FluTriangle.h"

FluTriangle::FluTriangle(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setFixedSize(24, 14);
    // FluStyleSheetUtils::setQssByFileName("../StyleSheet/light/FluTriangle.qss", this);
}

QList<QPoint> FluTriangle::getPointsByOrient(FluTriangleOrient orient)
{
    int top = 2;
    int bottom = this->height() - 2;
    int left = 2;
    int right = this->width() - 2;

    QList<QPoint> pos;
    if (orient == FluTriangleOrient::Top)
    {
        QPoint po1 = QPoint(left, bottom);
        QPoint po2 = QPoint(right, bottom);
        QPoint po3 = QPoint(this->width() / 2, top);

        pos.push_back(po1);
        pos.push_back(po2);
        pos.push_back(po3);
    }
    else if (orient == FluTriangleOrient::Bottom)
    {
        QPoint po1 = QPoint(0, 0);
        QPoint po2 = QPoint(width(), 0);
        QPoint po3 = QPoint(height(), width() / 2);

        pos.push_back(po1);
        pos.push_back(po2);
        pos.push_back(po3);
    }
    else if (orient == FluTriangleOrient::Left)
    {
        QPoint po1 = QPoint(width(), 0);
        QPoint po2 = QPoint(width(), height());
        QPoint po3 = QPoint(0, height() / 2);

        pos.push_back(po1);
        pos.push_back(po2);
        pos.push_back(po3);
    }
    else if (orient == FluTriangleOrient::Right)
    {
        QPoint po1 = QPoint(0, 0);
        QPoint po2 = QPoint(0, height());
        QPoint po3 = QPoint(width(), height() / 2);

        pos.push_back(po1);
        pos.push_back(po2);
        pos.push_back(po3);
    }

    return pos;
}

void FluTriangle::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(175, 175, 175));
    painter.setPen(pen);

    QBrush brush;
    brush.setColor(QColor(249, 249, 249));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    painter.drawPolygon(getPointsByOrient(FluTriangleOrient::Top));
#endif
}
