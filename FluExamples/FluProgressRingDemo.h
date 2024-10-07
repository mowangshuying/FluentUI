#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluProgressRing.h"
#include <QTimer>

class FluProgressRingDemo : public FluWidget
{
  public:
    FluProgressRingDemo(QWidget* parent = nullptr);

  protected:
    int m_nTimes;
};
