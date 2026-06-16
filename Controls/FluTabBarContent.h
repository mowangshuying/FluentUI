#pragma once

#include <QScrollArea>
#include <QHBoxLayout>

#include "FluTabBarItem.h"
#include <QScrollBar>
#include <QWheelEvent>

class FluTabBarContent : public QScrollArea
{
    Q_OBJECT
  public:
    FluTabBarContent(QWidget* parent = nullptr);

    void addBarItem(FluTabBarItem* item);

    void insertTabBarItem(int nPos, FluTabBarItem* item);

    void removeTabBarItem(FluTabBarItem* item);

    int getSelectedTabBarItemIndex();

    FluTabBarItem* getSelectedTabBarItem();

    std::vector<FluTabBarItem*> getTabBarItems();

    int getTabBarItemMaxWidth();

    void setTabBarItemMaxWidth(int nW);

    int getTabBarItemMinWidth();

    void setTabBarItemMinWidth(int nW);

    void wheelEvent(QWheelEvent* event);

    void resizeEvent(QResizeEvent* event);

  protected:
    QWidget* m_hMainWidget;
    QHBoxLayout* m_hMainLayout;
    QHBoxLayout* m_hLeftLayout;
    QHBoxLayout* m_hMidLayout;
    QHBoxLayout* m_hRightLayout;

    QPushButton* m_addTabBtn;

    int m_nTabBarItemMaxWidth;
    int m_nTabBarItemMinWidth;

    QPoint m_dragPoint;
    bool m_bDraging;
    std::vector<FluTabBarItem*> m_tabBarItems;
};
