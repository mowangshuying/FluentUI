#pragma once

#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "../FluUtils/FluUtils.h"

class FluScaleButton : public QPushButton
{
    Q_OBJECT
  public:
    FluScaleButton(FluAwesomeType awesomeType, QWidget* parent = nullptr);

    void initTimer();

    void scaleByPercentage(float scale);

    void mousePressEvent(QMouseEvent* e);

    void mouseReleaseEvent(QMouseEvent* e);

  public slots:
    void onThemeChanged();

  protected:
    FluAwesomeType m_iconType;
    QTimer* m_timer;
    float m_currentPercentage;
    bool m_bToBig;
    bool m_bPressed;
};
