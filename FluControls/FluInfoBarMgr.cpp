#include "FluInfoBarMgr.h"
#include "FluShortInfoBar.h"

FluInfoBarMgr::FluInfoBarMgr(QObject* parent /*= nullptr*/) : QObject(parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    connect(m_timer, &QTimer::timeout, [=]() {
        // if the first elem not at spec pos move it.
        // when move it , should move others.
        // top at 75;
        // the spcing fix 15
        // move infobar.
        for (auto itMap = m_infoBarMap.begin(); itMap != m_infoBarMap.end(); itMap++)
        {
            for (auto itList = itMap->infoBarList.begin(); itList != itMap->infoBarList.end(); itList++)
            {
                // the first move.
                if (itList == itMap->infoBarList.begin())
                {
                    if ((*itList)->y() > 75)
                    {
                        (*itList)->move((*itList)->x(), (*itList)->y() - 1);
                    }
                    continue;
                }

                // other.
                auto itPrevList = itList;
                itPrevList = itPrevList--;

                if ((*itList)->y() - ((*itPrevList)->y() + (*itPrevList)->height()) > 15)
                {
                    (*itPrevList)->move((*itPrevList)->x(), (*itPrevList)->y() - 1);
                }
            }
        }
    });

    // to start timer.
    m_timer->start();
}

void FluInfoBarMgr::addInfoBar(QWidget* parentWidget, FluShortInfoBar* infoBar)
{
    if (parentWidget == nullptr || infoBar == nullptr)
        return;

  //  long key = (long)(parentWidget);
  //  auto itf = m_infoBarMap.find(key);

    auto itf = m_infoBarMap.begin();
    for (;itf != m_infoBarMap.end(); itf++)
    {
        if (itf->parentWidget == parentWidget)
            break;

        //itf++;
    }

    if (itf == m_infoBarMap.end())
    {
        // set infoBar pos
        int nX = parentWidget->width() / 2 - infoBar->width() / 2;
        int nY = 75;

        infoBar->move(nX, nY);
        std::list<FluShortInfoBar*> infoBarList;
        infoBarList.push_back(infoBar);
       // m_infoBarMap[key] = infoBarList;
        
        FluInfoBarList list;
        list.parentWidget = parentWidget;
        list.infoBarList = infoBarList;

        m_infoBarMap.push_back(list);
        return;
    }

    int nX = parentWidget->width() / 2 - infoBar->width() / 2;
    int nY = itf->infoBarList.back()->y() + itf->infoBarList.back()->height() + 15;

    infoBar->move(nX, nY);
    itf->infoBarList.push_back(infoBar);
}

void FluInfoBarMgr::removeInfoBar(FluShortInfoBar* infoBar)
{
    for (auto itMap = m_infoBarMap.begin(); itMap != m_infoBarMap.end(); itMap++)
    {
        auto itf = std::find(itMap->infoBarList.begin(), itMap->infoBarList.end(), infoBar);
        if (itf != itMap->infoBarList.end())
        {
            itMap->infoBarList.erase(itf);
            break;
        }
    }
}
