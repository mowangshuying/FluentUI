#pragma once

#include "../FluControls/FluThread.h"
#include "../FluControls/FluWidget.h"
#include "../FluUtils/FluUtils.h"

class FluThreadDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluThreadDemo(QWidget* parent = nullptr);

    ~FluThreadDemo();

  protected:
    FluThread m_thread;
};
