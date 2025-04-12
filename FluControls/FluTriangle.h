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
    FluTriangle(QWidget* parent = nullptr);

    QList<QPoint> getPointsByOrient(FluTriangleOrient orient);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged()
    {
        // if (FluThemeUtils::isLightTheme())
        //{
        //     FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluTriangle.qss"), this);
        // }
        // else
        //{
        //     FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluTriangle.qss"), this);
        // }
    }
};
