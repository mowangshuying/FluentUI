#pragma once

#include "../Controls/FluWidget.h"
#include "../Controls/FluProgressRing.h"
#include <QTimer>

class FluProgressRingDemo : public FluWidget
{
  public:
    FluProgressRingDemo(QWidget* parent = nullptr);

  protected:
    int m_times;
};
