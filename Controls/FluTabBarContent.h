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

    void insertTabBarItem(int pos, FluTabBarItem* item);

    void removeTabBarItem(FluTabBarItem* item);

    int getSelectedTabBarItemIndex();

    FluTabBarItem* getSelectedTabBarItem();

    std::vector<FluTabBarItem*> getTabBarItems();

    int getTabBarItemMaxWidth();

    void setTabBarItemMaxWidth(int w);

    int getTabBarItemMinWidth();

    void setTabBarItemMinWidth(int w);

    void wheelEvent(QWheelEvent* event);

    void resizeEvent(QResizeEvent* event);

  protected:
    QWidget* m_mainWidget;
    QHBoxLayout* m_mainLayout;
    QHBoxLayout* m_leftLayout;
    QHBoxLayout* m_midLayout;
    QHBoxLayout* m_rightLayout;

    QPushButton* m_addTabButton;

    int m_tabBarItemMaxWidth;
    int m_tabBarItemMinWidth;

    QPoint m_dragPoint;
    bool m_isDraging;
    std::vector<FluTabBarItem*> m_tabBarItems;
};
