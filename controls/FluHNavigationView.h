#pragma once

#include "FluWidget.h"
#include <QHBoxLayout>

#include "FluHScrollView.h"
#include "FluHNavigationItem.h"

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

    void addItemToLayout(QWidget* item, FluHNavigationItemPosition pos);

    void setLastSelectedItem(FluHNavigationItem* item);

    FluHNavigationItem* getLastSelectedItem();

    void setFlyIconTextItem(FluHNavigationFlyIconTextItem* flyIconTextIcon);

    FluHNavigationFlyIconTextItem* getFlyIconTextIcon();

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
