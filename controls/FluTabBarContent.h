#pragma once

#include <QScrollArea>
#include <QHBoxLayout>

#include "FluTabBarItem.h"
#include <QScrollBar>
#include <QWheelEvent>

class FluTabBarPaintLayer;

class FluTabBarContent : public QScrollArea
{
    Q_OBJECT
    Q_PROPERTY(QColor tabHoverColor READ getTabHoverColor WRITE setTabHoverColor)
    Q_PROPERTY(QColor tabPressedColor READ getTabPressedColor WRITE setTabPressedColor)
    Q_PROPERTY(QColor tabSelectedColor READ getTabSelectedColor WRITE setTabSelectedColor)
    Q_PROPERTY(QColor tabSeparatorColor READ getTabSeparatorColor WRITE setTabSeparatorColor)
    Q_PROPERTY(QColor tabSelectedStrokeColor READ getTabSelectedStrokeColor WRITE setTabSelectedStrokeColor)
  public:
    FluTabBarContent(QWidget* parent = nullptr);

    QColor getTabHoverColor() const;
    void setTabHoverColor(QColor c);

    QColor getTabPressedColor() const;
    void setTabPressedColor(QColor c);

    QColor getTabSelectedColor() const;
    void setTabSelectedColor(QColor c);

    QColor getTabSeparatorColor() const;
    void setTabSeparatorColor(QColor c);

    QColor getTabSelectedStrokeColor() const;
    void setTabSelectedStrokeColor(QColor c);

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

    void updatePaintLayer();

  public slots:
    void onThemeChanged();

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

    FluTabBarPaintLayer* m_paintLayer = nullptr;

    QColor m_tabHoverColor;
    QColor m_tabPressedColor;
    QColor m_tabSelectedColor;
    QColor m_tabSeparatorColor;
    QColor m_tabSelectedStrokeColor;
};
