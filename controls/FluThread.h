#pragma once

#include <QThread>
#include <mutex>
#include <functional>

class FluThread : public QThread
{
    Q_OBJECT
  public:
    using FluThreadFunc = std::function<void(FluThread*)>;

  public:
    FluThread(QObject* parent = nullptr);

    void start(FluThreadFunc createFunc, FluThreadFunc runFunc, FluThreadFunc destoryFunc);

    // quit
    // isRunning

    void run();

  protected:
    FluThreadFunc m_onCreate;
    FluThreadFunc m_onRun;
    FluThreadFunc m_onDestory;
};
