#pragma once

#include "../FluControls/FluThread.h"
#include "../FluControls/FluWidget.h"
#include "../FluUtils/FluUtils.h"

class FluThreadDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluThreadDemo(QWidget* parent = nullptr) : FluWidget(parent)
    {
        m_thread.start([](FluThread* thread) { LOG_DEBUG << "Start..."; },
                       [](FluThread* thread) {
                           // while (true)
                           // {
                           LOG_DEBUG << "Running...";
                           // }
                       },

                       [](FluThread* thread) { LOG_DEBUG << "End..."; });
        resize(600, 400);
    }

    ~FluThreadDemo()
    {
        m_thread.quit();
        m_thread.wait();
    }

  protected:
    FluThread m_thread;
};
