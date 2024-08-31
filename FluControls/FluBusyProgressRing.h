#pragma once

#include "FluWidget.h"
#include <QPainter>
#include <QtMath>
#include <QTimer>
#include "../FluUtils/FluUtils.h"

class FluBusyProgressRing : public FluWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor circleColor READ getCircleColor WRITE setCircleColor)
  public:
    class WorkData
    {
      public:
        int m_workAngle;
        QPointF m_point;
    };

  public:
    FluBusyProgressRing(QWidget* parent = nullptr);

    QColor getCircleColor();

    void setCircleColor(QColor color);

    QPointF getPoint(int angle);

    int getSpeed(int angle);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    QTimer* m_workingTimer;
    int m_nTimes;
    int m_workAngle;
    QPointF m_point;

    QColor m_circleColor;
    std::vector<WorkData> m_workDatas;
};
