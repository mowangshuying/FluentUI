#pragma once

#include "FluWidget.h"
#include "../FluUtils/FluUtils.h"
#include <QPaintEvent>
#include <QPainter>
#include <QStyleOption>
#include <vector>

class FluTriangle : public FluWidget
{
    Q_OBJECT
  public:
    enum class FluTriangleOrient
    {
        Top,
        Bottom,
        Left,
        Right,
    };

  public:
    FluTriangle(QWidget* parent = nullptr) : FluWidget(parent)
    {
        setFixedSize(20, 10);
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTriangle.qss", this);
    }

    QList<QPoint> getPointsByOrient(FluTriangleOrient orient)
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

    void paintEvent(QPaintEvent* event)
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
        pen.setColor(QColor(192, 192, 192));
        painter.setPen(pen);

        QBrush brush;
        brush.setColor(QColor(249, 249, 249));
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);

        painter.drawPolygon(getPointsByOrient(FluTriangleOrient::Top));
    }
  public slots:
    void onThemeChanged()
    {
        // if (FluThemeUtils::isLightTheme())
        //{
        //     FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTriangle.qss", this);
        // }
        // else
        //{
        //     FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTriangle.qss", this);
        // }
    }
};
