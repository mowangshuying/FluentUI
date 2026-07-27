#pragma once

#include "../controls/FluWidget.h"
#include "../controls/FluProgressRing.h"
#include <QTimer>

class FluProgressRingDemo : public FluWidget
{
  public:
    FluProgressRingDemo(QWidget* parent = nullptr);

  protected:
    int m_times;
};
