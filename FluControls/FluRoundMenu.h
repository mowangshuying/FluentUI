#pragma once

#include <QMenu>
#include <list>
#include <QHBoxLayout>
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include "FluRoundMenuView.h"

class FluSubMenuItemWidget;
class FluMenuAniMgr;
class FluRoundMenu : public QMenu
{
    Q_OBJECT
  public:
    FluRoundMenu(QString title, QWidget* parent = nullptr);

  public:

    void setMaxVisibleItems(int num);

    void setItemHeight(int height);

    FluRoundMenuView* getView();

    void setShadowEffect(int blurRadius = 30, QPoint offset = QPoint(0, 8), QColor color = QColor(0, 0, 0, 30));

    void setParentMenu(FluRoundMenu* menu, QListWidgetItem* item);

    void adjustSize();

    QPixmap getIcon();

    void setIcon(QPixmap icon);

    QString getTitle();

    void clear();

    void addAction(QAction* action);

    QListWidgetItem* _createActionItem(QAction* action, QAction* preAction = nullptr);

    int _adjustItemText(QListWidgetItem* item, QAction* action);

    int calcShortcutWidth();

    QIcon makeItemIcon(QAction* action);

    QIcon makeItemIcon(FluRoundMenu* menu);

    bool hasMenuItemIcon();

    void insertAction(QAction* before, QAction* action);

    void addActions(const QList<QAction*> actions);

    void insertActions(QAction* before, const QList<QAction*>& actions);

    void removeAction(QAction* action);

    void setDefaultAction(QAction* action);

    void setDefaultAction(int nIndex);

    void addMenu(FluRoundMenu* menu);

    void insertMenu(QAction* before, FluRoundMenu* menu);

    FluSubMenuItemWidget* _createSubMenuItem(FluRoundMenu* menu);

    void addSeparator();

    void hideMenu(bool bHideBySystem = false);

    void closeParentMenu();

    QList<QAction*> getMenuActions();

    void adjustPosition();

    void exec(QPoint pos, bool bAni = true, FluMenuAniType aniType = FluMenuAniType::dropDown);

  signals:
    void closedSignal();
  public slots:

    void onShowMenuTimeOut();

    void onItemClicked(QListWidgetItem* item);

    void onItemEntered(QListWidgetItem* item);

    void onActionChanged();

    void onShowSubMenu(QListWidgetItem* item);
  protected:
    void hideEvent(QHideEvent* event);

    void closeEvent(QCloseEvent* event);

    void mousePressEvent(QMouseEvent* event);

    void mouseMoveEvent(QMouseEvent* event);

  protected:
    bool m_bSubMenu;
    bool m_bHideBySystem;
    int m_itemHeight;

    QString m_title;
    QPixmap m_icon;

    FluRoundMenu* m_parentMenu = nullptr;
    
    QListWidgetItem* m_menuItem;
    QListWidgetItem* m_lastHoverItem;
    QListWidgetItem* m_lastHoverSubMenuItem;

    QHBoxLayout* m_hBoxLayout;
    FluRoundMenuView* m_roundMenuView;
    FluMenuAniMgr* m_aniMgr;

    QTimer* m_timer;

    QList<QAction*> m_actions;
    QList<FluRoundMenu*> m_subMenus;
    QGraphicsDropShadowEffect* m_shadowEffect;
};
