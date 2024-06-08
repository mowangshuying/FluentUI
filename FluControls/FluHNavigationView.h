#pragma once

#include "FluWidget.h"
#include <QHBoxLayout>

#include "FluHScrollView.h"

#include <QStyleOption>
#include <QPainter>

class FluHNavigationIconTextItem;
class FluHNavigationMoreItem;
class FluHNavigationItem;
class FluHNavigationView : public FluWidget
{
    Q_OBJECT
  public:
    FluHNavigationView(QWidget* parent = nullptr);

    void addItemToLeftLayout(QWidget* item);

    void addItemToMidLayout(QWidget* item);

    void addItemToRightLayout(QWidget* item);

    void removeItemMidLayout(QWidget* item);

    // QSize minimumSizeHint()
    //{
    //      return QSize(120, 40);
    // }
    void setLastSelectedItem(FluHNavigationItem* item)
    {
        m_lastSelectedItem = item;
    }

    FluHNavigationItem* getLastSelectedItem()
    {
        return m_lastSelectedItem;
    }

    void clearAllItemsSelectState();
    void updateAllItemsStyleSheet();

    void resizeEvent(QResizeEvent* event);

    void paintEvent(QPaintEvent* event);

  protected:
    std::vector<FluHNavigationIconTextItem*> m_items;
    QHBoxLayout* m_hLayout;
    QWidget* m_leftWrapWidget;
    // FluHScrollView* m_midHScrollView;
    QWidget* m_MidWrapWidget;
    QWidget* m_rightWrapWidget;

    QHBoxLayout* m_hLeftWrapLayout;
    // QHBoxLayout* m_hMidWrapLayout;
    QHBoxLayout* m_hRightWrapLayout;

    FluHNavigationMoreItem* m_moreItem;

    FluHNavigationItem* m_lastSelectedItem;
};
