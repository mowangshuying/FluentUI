#pragma once

#include "FluHNavigationItem.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include "../Utils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "FluHNavigationIndicator.h"

class FluHNavigationFlyIconTextItem;
class FluHNavigationIconTextItem : public FluHNavigationItem
{
    Q_OBJECT
  public:
    FluHNavigationIconTextItem(QWidget* parent = nullptr);

    FluHNavigationIconTextItem(FluAwesomeType awesomeType, QString text, QWidget* parent = nullptr);

    FluHNavigationIconTextItem(QString text, QWidget* parent = nullptr);

    FluHNavigationIconTextItem(FluHNavigationIconTextItem* item);

    ~FluHNavigationIconTextItem();

    void itemClone(FluHNavigationIconTextItem* item);

    std::vector<FluHNavigationIconTextItem*> getItems();

    void getAllItems(std::vector<FluHNavigationIconTextItem*>& totalItems);

    std::vector<FluHNavigationIconTextItem*> getAllItems();

    QWidget* getWrapWidget1();

    QWidget* getWrapWidget2();

    QPushButton* getIconButton();

    QLabel* getLabel();

    FluAwesomeType getAwesomeType();

    QString getText();

    bool getHideIcon();

    void setHideIcon(bool isHideIcon);

    bool parentIsFlyIconTextItem();

    bool parentIsNavigationView();

    void setParentIsFlyIconTextItem(bool isParent);

    void setParentIsNavigationView(bool isParent);

    void setParentFlyIconTextItem(FluHNavigationFlyIconTextItem* parentFlyIconTextItem);

    FluHNavigationFlyIconTextItem* getParentFlyIconTextItem();

    void addItem(FluHNavigationIconTextItem* item);

    int calcItemW1Width();

    int calcItemWidth();

    int calcItemW2Height(FluHNavigationIconTextItem* item);

    void adjustItemHeight(FluHNavigationIconTextItem* item);

    void adjustItemWidth(FluHNavigationIconTextItem* item, int& maxWidth, int& callHierarchy);

    void setItemFixedWidth(int maxWidth);

    void setArrowButtonToChevronUp();

    void setArrowButtonToChevronDown();

    int getDepth();

    FluHNavigationIconTextItem* getRootItem();

    bool isLeaf();

    void expand();

    void collapse();

    void clearAllItemsSelectState();

    void clearAllItemsSelectState(FluHNavigationIconTextItem* item);

    void updateAllItemsStyleSheet();

    void updateAllItemsStyleSheet(FluHNavigationIconTextItem* item);

    void updateSelected(bool b);

    QWidget* getVerticalIndicator();

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void itemClicked();
  public slots:
    void onItemClicked();

    void onThemeChanged();
    void updateIconTheme();

  protected:
    QWidget* m_wrapWidget1;
    QWidget* m_wrapWidget2;

    QWidget* m_emptyWidget;

    QWidget* m_horizontalIndicatorWrap;
    QHBoxLayout* m_horizontalIndicatorLayout;
    FluHNavigationIndicator* m_horizontalIndicator;

    QWidget* m_verticalIndicator;
    QPushButton* m_iconButton;
    QLabel* m_label;
    QPushButton* m_arrow;
    QHBoxLayout* m_horizontalLayout1;

    std::vector<FluHNavigationIconTextItem*> m_items;

    QVBoxLayout* m_mainLayout;
    QVBoxLayout* m_verticalLayout1;

    FluHNavigationIconTextItem* m_parentItem;
    FluHNavigationFlyIconTextItem* m_parentFlyIconTextItem;
    FluAwesomeType m_awesomeType;

    bool m_isHideIcon;
    bool m_isSelected;
    bool m_isDown;

    bool m_isParentIsFlyIconTextItem;
    bool m_isParentIsNavigationView;
};
