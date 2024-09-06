#pragma once

#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <qmatrix4x4.h>
#include <QPixmap>
#include "../FluUtils/FluIconUtils.h"
#include "../FluUtils/FluUtils.h"

class FluRotationButton : public QPushButton
{
    Q_OBJECT
  public:
    FluRotationButton(QWidget* parent = nullptr);

    FluRotationButton(FluAwesomeType awesomeType, QWidget* parent = nullptr);

    void setAwesomeType(FluAwesomeType awesomeType);

    void setRotation(bool b);

    void setReserveAngle(int nReserveAngle);

  public slots:
    void onTimeOut();

    void onThemeChanged();

  protected:
    FluAwesomeType m_awesomeType;
    QTimer* m_timer;
    QColor m_penColor;
    int m_nAngle;
    int m_nReserveAngle;
    bool m_bRotation;
};
