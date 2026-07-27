#pragma once

#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <qmatrix4x4.h>
#include <QPixmap>
#include "../Utils/FluIconUtils.h"
#include "../Utils/FluUtils.h"

class FluRotationButton : public QPushButton
{
    Q_OBJECT
  public:
    FluRotationButton(QWidget* parent = nullptr);

    FluRotationButton(FluAwesomeType awesomeType, QWidget* parent = nullptr);

    void setAwesomeType(FluAwesomeType awesomeType);

    void setRotation(bool b);

    void setReserveAngle(int reserveAngle);

  public slots:
    void onTimeOut();

    void onThemeChanged();

  protected:
    FluAwesomeType m_awesomeType;
    QTimer* m_timer;
    QColor m_penColor;
    int m_angle;
    int m_reserveAngle;
    bool m_isRotation;
};
