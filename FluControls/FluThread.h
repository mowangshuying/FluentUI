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
	  FluThread(QObject* parent = nullptr) : QThread(parent)
	  {

	  }

	  void start(FluThreadFunc createFunc, FluThreadFunc runFunc, FluThreadFunc destoryFunc)
	  {
              if (createFunc != nullptr)
                  m_onCreate = createFunc;

			  if (runFunc != nullptr)
                  m_onRun = runFunc;

			  if (destoryFunc != nullptr)
                  m_onDestory = destoryFunc;

			  QThread::start();
	  }

	  // quit
	  // isRunning

	  void run()
	  {
           if (m_onCreate != nullptr)
               m_onCreate(this);

		   if (m_onRun != nullptr)
               m_onRun(this);

		   if (m_onDestory != nullptr)
               m_onDestory(this);
	  }

 protected:
      FluThreadFunc m_onCreate;
	  FluThreadFunc m_onRun;
      FluThreadFunc m_onDestory;


};
