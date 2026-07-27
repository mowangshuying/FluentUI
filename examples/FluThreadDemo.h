#pragma once

#include "../Controls/FluThread.h"
#include "../Controls/FluWidget.h"
#include "../Utils/FluUtils.h"

class FluThreadDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluThreadDemo(QWidget* parent = nullptr);

    ~FluThreadDemo();

  protected:
    FluThread m_thread;
};
