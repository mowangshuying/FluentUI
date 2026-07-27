#pragma once

#include "../controls/FluThread.h"
#include "../controls/FluWidget.h"
#include "../utils/FluUtils.h"

class FluThreadDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluThreadDemo(QWidget* parent = nullptr);

    ~FluThreadDemo();

  protected:
    FluThread m_thread;
};
