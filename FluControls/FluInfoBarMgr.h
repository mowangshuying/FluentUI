#pragma once

// #include "FluShortInfoBar.h"
#include <map>
#include <list>
#include <QTimer>
#include <algorithm>

class FluShortInfoBar;

// class FluInfoBarList
//{
//   public:
//     QWidget* parentWidget;
//     std::list<FluShortInfoBar*> infoBarList;
// };

class FluInfoBarMgr : public QObject
{
    Q_OBJECT
  public:
    FluInfoBarMgr(QObject* parent = nullptr);

    ~FluInfoBarMgr();

    static FluInfoBarMgr* getInstance()
    {
        static FluInfoBarMgr mgr;
        return &mgr;
    }

    void addInfoBar(QWidget* parentWidget, FluShortInfoBar* infoBar, int nDisappearDuration = 800);

    void removeInfoBar(FluShortInfoBar* infoBar);

   // void stopTimer()
   // {
   //     m_timer->stop();
  //  }

    bool eventFilter(QObject* watched, QEvent* event);
  protected:
    std::map<QWidget*, std::list<FluShortInfoBar*>> m_infoBarMap;
    QTimer* m_timer;
};
