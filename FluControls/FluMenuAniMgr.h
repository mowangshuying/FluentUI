#pragma once
#include <QtCore>
#include <QObject>
#include <QPropertyAnimation>
#include <QApplication>
#include <QScreen>
#include <QHoverEvent>

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#include <QtMinMax>
#endif

#include "FluRoundMenuView.h"
#include "FluMenuAniType.h"

class FluRoundMenu;
class FluMenuAniMgr : public QObject
{
  public:
    FluMenuAniMgr(FluRoundMenu* menu, FluMenuAniType aniType = FluMenuAniType::none);

  public:
    virtual QSize availableViewSize(QPoint pos);
    virtual QPoint calcFinalPos(QPoint pos);

    QSize getMenuSize();

    virtual void exec(QPoint pos);
    static FluMenuAniMgr* make(FluRoundMenu* roundMenu, FluMenuAniType type);

  public slots:
    virtual void onValueChanged();

    virtual void updateMenuViewport();

  protected:
    FluRoundMenu* m_menu;
    QPropertyAnimation* m_posAni;
    FluMenuAniType m_menuAniType;
};
