#pragma once

#include <QWidget>
#include <map>
#include <list>
#include <QPoint>

class FluInfoBar;
enum class FluInfoBarSeverity;

enum class FluInfoBarPosition
{
    TopCenter,
    BottomRight,
};

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

    static void showInfoBar(QWidget* parentWidget, FluInfoBarSeverity severity, QString text, bool isCloseable = true,
                            FluInfoBarPosition position = FluInfoBarPosition::TopCenter);

    void addInfoBar(QWidget* parentWidget, FluInfoBar* infoBar, int disappearDuration = 800,
                    FluInfoBarPosition position = FluInfoBarPosition::TopCenter);

    void removeInfoBar(FluInfoBar* infoBar);

    bool eventFilter(QObject* watched, QEvent* event) override;

  protected:
    FluInfoBarPosition positionOf(QWidget* parentWidget) const;
    void setPosition(QWidget* parentWidget, FluInfoBarPosition position);

    QPoint targetPosition(QWidget* parentWidget, FluInfoBar* infoBar);
    void relayout(QWidget* parentWidget);
    void animateTo(FluInfoBar* bar, const QPoint& target);

    std::map<QWidget*, std::list<FluInfoBar*>> m_infoBarMap;
    std::map<QWidget*, FluInfoBarPosition> m_positionMap;
};