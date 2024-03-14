#include "FluInfoBarMgr.h"
#include "FluShortInfoBar.h"

FluInfoBarMgr::FluInfoBarMgr(QObject* parent /*= nullptr*/) : QObject(parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1);

    connect(m_timer, &QTimer::timeout, [&]() {
        // if the first elem not at spec pos move it.
        // when move it , should move others.
        // top at 75;
        // the spcing fix 15
        // move infobar.

        //   if (m_infoBarMap.empty())
        //       m_timer->stop();

        for (auto itMap = m_infoBarMap.begin(); itMap != m_infoBarMap.end(); itMap++)
        {
            for (auto itList = itMap->second.begin(); itList != itMap->second.end(); itList++)
            {
                // the first move.
                if (itList == itMap->second.begin())
                {
                    if ((*itList)->y() > 75)
                    {
                        (*itList)->move((*itList)->x(), (*itList)->y() - 1);
                    }

                    // the first;
                    //(*itList)->setDisappearDuration()

                    (*itList)->disappear();
                    continue;
                }

                // other.
                auto itPrevList = itList;
                itPrevList--;

                //  LOG_DEBUG << "Y1:" << (*itList)->y();
                //  LOG_DEBUG << "Y2:" << (*itPrevList)->y();
                //  LOG_DEBUG << "H:" << (*itPrevList)->height();

                if ((*itList)->y() - ((*itPrevList)->y() + (*itPrevList)->height()) > 15)
                {
                    (*itList)->move((*itList)->x(), (*itList)->y() - 1);
                }
            }
        }
    });

    // to start timer.
    // m_timer->start();
    m_timer->start();
    m_infoBarMap.clear();
}

void FluInfoBarMgr::addInfoBar(QWidget* parentWidget, FluShortInfoBar* infoBar, int nDisappearDuration /* = 2000*/)
{
    if (parentWidget == nullptr || infoBar == nullptr)
        return;

    //  long key = (long)(parentWidget);
    //  auto itf = m_infoBarMap.find(key);

    // infoBar->show();
    // infoBar->hide();

    infoBar->setDisappearDurartion(nDisappearDuration);
    auto itf = m_infoBarMap.find(parentWidget);
    if (itf == m_infoBarMap.end())
    {
        // set infoBar pos
        int nX = parentWidget->width() / 2 - infoBar->sizeHint().width() / 2;
        // LOG_DEBUG << "parentWidget Width:" << parentWidget->width() << ", infoBar width:" << infoBar->width();
        int nY = 75;

        infoBar->move(nX, nY);
        infoBar->show();

        std::list<FluShortInfoBar*> infoBarList;
        infoBarList.push_back(infoBar);
        m_infoBarMap[parentWidget] = infoBarList;
        return;
    }

    int nX = parentWidget->width() / 2 - infoBar->sizeHint().width() / 2;
    int nY = itf->second.back()->y() + itf->second.back()->height() + 15;

    infoBar->move(nX, nY);
    infoBar->show();
    itf->second.push_back(infoBar);
}

void FluInfoBarMgr::removeInfoBar(FluShortInfoBar* infoBar)
{
    for (auto itMap = m_infoBarMap.begin(); itMap != m_infoBarMap.end(); itMap++)
    {
        auto itf = std::find(itMap->second.begin(), itMap->second.end(), infoBar);
        if (itf != itMap->second.end())
        {
            itMap->second.erase(itf);
            //  m_timer->start();
            break;
        }
    }

    for (auto itMap = m_infoBarMap.begin(); itMap != m_infoBarMap.end();)
    {
        if (itMap->second.empty())
        {
            itMap = m_infoBarMap.erase(itMap);
            continue;
        }
        itMap++;
    }
}
