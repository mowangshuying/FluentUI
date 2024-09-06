#pragma once

#include "FluWidget.h"
#include <QPainter>
#include <QTimer>
#include "../FluUtils/FluUtils.h"

class FluProgressRing : public FluWidget
{
    Q_OBJECT
  public:
    FluProgressRing(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

    void setMinMaxValue(int minValue, int maxValue);

    void setCurValue(int curValue);

    int getCurValue();

    bool getWorking();

    void setWorking(bool bWorking);

    void setShowText(bool bShowText);

    bool getShowText();

    bool getTransparentTrack();

    void setTransparentTrack(bool bTransparentTrack);

  protected:
    int m_minValue;
    int m_maxValue;
    int m_curValue;

    int m_workStartValue;
    bool m_bWorking;
    bool m_bShowText;
    bool m_bTransparentTrack;
    QTimer* m_workingTimer;
};
