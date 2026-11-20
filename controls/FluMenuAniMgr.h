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

  protected:
    // Global rect of the control that opens this menu, or an invalid rect when
    // `pos` was not derived from that control's bottom-left corner.
    QRect anchorRect(QPoint pos) const;

    // True when a dropDown popup does not fit below its anchor while the upper
    // side has more room, i.e. it has to open upwards instead.
    bool shouldFlipUp(QPoint pos) const;

  public slots:
    virtual void onValueChanged();

    virtual void updateMenuViewport();

  protected:
    FluRoundMenu* m_menu;
    QPropertyAnimation* m_posAni;
    FluMenuAniType m_menuAniType;
};
