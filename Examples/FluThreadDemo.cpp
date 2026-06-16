#include "FluThreadDemo.h"

FluThreadDemo::FluThreadDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
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

FluThreadDemo::~FluThreadDemo()
{
    m_thread.quit();
    m_thread.wait();
}
