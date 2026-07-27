#include "FluThread.h"

FluThread::FluThread(QObject* parent /*= nullptr*/) : QThread(parent)
{
}

void FluThread::start(FluThreadFunc createFunc, FluThreadFunc runFunc, FluThreadFunc destoryFunc)
{
    if (createFunc != nullptr)
        m_onCreate = createFunc;

    if (runFunc != nullptr)
        m_onRun = runFunc;

    if (destoryFunc != nullptr)
        m_onDestory = destoryFunc;

    QThread::start();
}

void FluThread::run()
{
    if (m_onCreate != nullptr)
        m_onCreate(this);

    if (m_onRun != nullptr)
        m_onRun(this);

    if (m_onDestory != nullptr)
        m_onDestory(this);
}
