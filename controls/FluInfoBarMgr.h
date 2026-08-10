#pragma once

#include <QWidget>
#include <map>
#include <list>
#include <QPoint>

class FluShortInfoBar;
enum class FluShortInfoBarType;

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

    static void showInfoBar(QWidget* parentWidget, FluShortInfoBarType type, QString text, bool isCloseable = true);

    void addInfoBar(QWidget* parentWidget, FluShortInfoBar* infoBar, int disappearDuration = 800);

    void removeInfoBar(FluShortInfoBar* infoBar);

    bool eventFilter(QObject* watched, QEvent* event) override;

  protected:
    QPoint targetPosition(QWidget* parentWidget, FluShortInfoBar* infoBar);
    void relayout(QWidget* parentWidget);
    void animateTo(FluShortInfoBar* bar, const QPoint& target);

    std::map<QWidget*, std::list<FluShortInfoBar*>> m_infoBarMap;
};