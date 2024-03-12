#pragma once

// #include "FluShortInfoBar.h"
#include <map>
#include <list>
#include <QTimer>
#include <algorithm>

class FluShortInfoBar;

class FluInfoBarList
{
  public:
    QWidget* parentWidget;
    std::list<FluShortInfoBar*> infoBarList;
};

class FluInfoBarMgr : public QObject
{
    Q_OBJECT
  public:
    FluInfoBarMgr(QObject* parent = nullptr);

    static FluInfoBarMgr* getInstance()
    {
        FluInfoBarMgr mgr;
        return &mgr;
    }

    void addInfoBar(QWidget* parentWidget, FluShortInfoBar* infoBar);

    void removeInfoBar(FluShortInfoBar* infoBar);

  protected:
    std::list<FluInfoBarList> m_infoBarMap;
    QTimer* m_timer;
};
