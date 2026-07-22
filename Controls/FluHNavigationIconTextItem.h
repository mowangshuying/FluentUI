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

    std::vector<FluHNavigationIconTextItem*> getItems()
    {
        return m_items;
    }

    void getAllItems(std::vector<FluHNavigationIconTextItem*>& totalItems);

    std::vector<FluHNavigationIconTextItem*> getAllItems();

    QWidget* getWrapWidget1()
    {
        return m_wrapWidget1;
    }

    QWidget* getWrapWidget2()
    {
        return m_wrapWidget2;
    }

    QPushButton* getIconButton()
    {
        return m_iconButton;
    }

    QLabel* getLabel()
    {
        return m_label;
    }

    FluAwesomeType getAwesomeType()
    {
        return m_awesomeType;
    }

    QString getText()
    {
        return m_label->text();
    }

    bool getHideIcon()
    {
        return m_isHideIcon;
    }

    void setHideIcon(bool isHideIcon)
    {
        m_isHideIcon = isHideIcon;
    }

    bool parentIsFlyIconTextItem()
    {
        return m_isParentIsFlyIconTextItem;
    }

    bool parentIsNavigationView()
    {
        return m_isParentIsNavigationView;
    }

    void setParentIsFlyIconTextItem(bool isParent)
    {
        m_isParentIsFlyIconTextItem = isParent;
    }

    void setParentIsNavigationView(bool isParent)
    {
        if (isParent)
        {
            m_horizontalIndicator->show();
        }
        else
        {
            m_horizontalIndicatorWrap->hide();
        }
        m_isParentIsNavigationView = isParent;
    }

    void setParentFlyIconTextItem(FluHNavigationFlyIconTextItem* parentFlyIconTextItem)
    {
        // m_horizontalIndicator->show();
        m_parentFlyIconTextItem = parentFlyIconTextItem;
    }

    FluHNavigationFlyIconTextItem* getParentFlyIconTextItem()
    {
        return m_parentFlyIconTextItem;
    }

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

    bool isLeaf()
    {
        return m_items.empty();
    }

    void expand();

    void collapse();

    void clearAllItemsSelectState();

    void clearAllItemsSelectState(FluHNavigationIconTextItem* item);

    void updateAllItemsStyleSheet();

    void updateAllItemsStyleSheet(FluHNavigationIconTextItem* item);

    void updateSelected(bool b);

    QWidget* getVerticalIndicator()
    {
        return m_verticalIndicator;
    }

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
  signals:
    void itemClicked();
  public slots:
    void onItemClicked();

    void onThemeChanged();

  protected:
    QWidget* m_wrapWidget1;
    QWidget* m_wrapWidget2;

    QWidget* m_emptyWidget;

    QWidget* m_horizontalIndicatorWrap;
    QHBoxLayout* m_horizontalIndicatorLayout;
    QWidget* m_horizontalIndicator;

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
