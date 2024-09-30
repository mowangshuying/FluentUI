#include "FluTriangle.h"

FluTriangle::FluTriangle(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setFixedSize(24, 14);
    // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTriangle.qss", this);
}

QList<QPoint> FluTriangle::getPointsByOrient(FluTriangleOrient orient)
{
    int nTop = 2;
    int nBottom = height() - 2;
    int nLeft = 2;
    int nRight = width() - 2;

    int nWidth = width();
    int nHeight = height();

    QList<QPoint> pos;
    if (orient == FluTriangleOrient::Top)
    {
        QPoint po1 = QPoint(nLeft, nBottom);
        QPoint po2 = QPoint(nRight, nBottom);
        QPoint po3 = QPoint(nWidth / 2, nTop);

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
    // QStyleOption opt;
    // opt.initFrom(this);
    // QPainter painter(this);
    // style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

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
