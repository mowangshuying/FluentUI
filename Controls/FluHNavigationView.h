#pragma once

#include "FluWidget.h"
#include <QHBoxLayout>

#include "FluHScrollView.h"

#include <QStyleOption>
#include <QPainter>

class FluHNavigationIconTextItem;
class FluHNavigationMoreItem;
class FluHNavigationItem;
class FluHNavigationFlyIconTextItem;


class FluHNavigationView : public FluWidget
{
    Q_OBJECT
  public:
    FluHNavigationView(QWidget* parent = nullptr);


    void addItemToLeftLayout(QWidget* item);

    void addItemToMidLayout(QWidget* item);

    void addItemToRightLayout(QWidget* item);

    void setLastSelectedItem(FluHNavigationItem* item)
    {
        m_lastSelectedItem = item;
    }

    FluHNavigationItem* getLastSelectedItem()
    {
        return m_lastSelectedItem;
    }

    void setFlyIconTextItem(FluHNavigationFlyIconTextItem* flyIconTextIcon)
    {
        m_FlyIconTextItem = flyIconTextIcon;
    }

    FluHNavigationFlyIconTextItem* getFlyIconTextIcon()
    {
        return m_FlyIconTextItem;
    }

    std::vector<FluHNavigationIconTextItem*> getHideItems();

    void clearAllItemsSelectState();
    void updateAllItemsStyleSheet();

    void resizeEvent(QResizeEvent* event);

    void paintEvent(QPaintEvent* event);

  signals:
    void keyChanged(QString key);

  protected:
    std::vector<FluHNavigationIconTextItem*> m_items;
    std::vector<FluHNavigationIconTextItem*> m_hideItems;

    QHBoxLayout* m_layout;
    QWidget* m_leftWrapWidget;
    QWidget* m_MidWrapWidget;
    QWidget* m_rightWrapWidget;

    QHBoxLayout* m_leftWrapLayout;
    QHBoxLayout* m_rightWrapLayout;

    FluHNavigationMoreItem* m_moreItem;

    FluHNavigationItem* m_lastSelectedItem;
    FluHNavigationFlyIconTextItem* m_FlyIconTextItem;
};
