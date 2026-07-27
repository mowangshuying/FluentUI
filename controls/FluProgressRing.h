#pragma once

#include "FluWidget.h"
#include <QPainter>
#include <QTimer>
#include "../Utils/FluUtils.h"

class FluProgressRing : public FluWidget
{
    Q_OBJECT
  public:
    FluProgressRing(QWidget* parent = nullptr);

    ~FluProgressRing()
    {
        m_workingTimer->stop();
    }

    void paintEvent(QPaintEvent* event);

    void setMinMaxValue(int minValue, int maxValue);

    void setCurValue(int curValue);

    int getCurValue();

    bool getWorking();

    void setWorking(bool isWorking);

    void setShowText(bool isShowText);

    bool getShowText();

    bool getTransparentTrack();

    void setTransparentTrack(bool isTransparentTrack);

  protected:
    int m_minValue;
    int m_maxValue;
    int m_curValue;

    int m_workStartValue;
    bool m_isWorking;
    bool m_isShowText;
    bool m_isTransparentTrack;
    QTimer* m_workingTimer;
};
