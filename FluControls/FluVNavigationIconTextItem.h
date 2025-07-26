#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QScrollArea>
#include <QStyleOption>
#include <QTransform>
#include <QVBoxLayout>
#include "FluWidget.h"
#include "FluVNavigationItem.h"
#include "../FluUtils/FluUtils.h"
#include <stack>

class FluVNavigationView;
class FluVNavigationIconTextItem : public FluVNavigationItem
{
    Q_OBJECT
  public:
    FluVNavigationIconTextItem(QWidget *parent = nullptr);

    FluVNavigationIconTextItem(QIcon icon, QString text, QWidget *parent = nullptr);

    FluVNavigationIconTextItem(FluAwesomeType awesomeType, QString text, QWidget *parent = nullptr);

    FluVNavigationIconTextItem(QString text, QWidget *parent = nullptr);

    FluVNavigationIconTextItem(FluVNavigationIconTextItem *item, QWidget *parent = nullptr);

    ~FluVNavigationIconTextItem()
    {
        // LOG_DEBUG << "called";
    }

    void itemClone(FluVNavigationIconTextItem *item);

    QWidget *getWrapWidget1()
    {
        return m_wrapWidget1;
    }

    QWidget *getWrapWidget2()
    {
        return m_wrapWidget2;
    }

    QPushButton *getIconBtn()
    {
        return m_iconBtn;
    }

    QLabel *getLabel()
    {
        return m_label;
    }

    FluAwesomeType getAwesomeType()
    {
        return m_awesomeType;
    }

    bool getHideIcon()
    {
        return m_bHideIcon;
    }

    void hideLabelArrow()
    {
        m_label->hide();
        m_arrow->hide();
    }

    void showLabelArrow()
    {
        m_label->show();
        if (!m_items.empty())
            m_arrow->show();
    }

    FluVNavigationIconTextItem *getParentItem()
    {
        return m_parentItem;
    }

    void setItemWidth(int nWidth);

    std::vector<FluVNavigationIconTextItem *> getItems();
    void getAllItems(std::vector<FluVNavigationIconTextItem *> &totalItems);
    std::vector<FluVNavigationIconTextItem *> getAllItems();

    void addItem(FluVNavigationIconTextItem *item);

    int calcItemW1Width();
    int calcItemWidth();
    int calcItemW2Height(FluVNavigationIconTextItem *item);

    void adjustItemWidth();
    void adjustItemWidth(FluVNavigationIconTextItem *item);
    void adjustItemHeight(FluVNavigationIconTextItem *item);

    void adjustFlyItemHeight(FluVNavigationFlyIconTextItem *flyItem);

    void adjustFlyItemWidth(FluVNavigationFlyIconTextItem *flyItem);

    int getDepth();

    void updateDepth(FluVNavigationIconTextItem *item);

    FluVNavigationIconTextItem *getRootItem();

    void clearAllItemsSelectState()
    {
        FluVNavigationIconTextItem *rootItem = getRootItem();
        clearItemsSelectState(rootItem);
    }

    void clearItemsSelectState(FluVNavigationIconTextItem *item);

    void updateAllItemsStyleSheet()
    {
        FluVNavigationIconTextItem *rootItem = getRootItem();
        updateItemsStyleSheet(rootItem);
    }

    void updateItemsStyleSheet(FluVNavigationIconTextItem *item);

    void updateSelected(bool b);

    void enableThisItem(bool b);

    bool isDown()
    {
        return m_bDown;
    }

    bool isLeaf()
    {
        return m_items.empty();
    }

    void mouseReleaseEvent(QMouseEvent *event) override;

    // to enable qss
    void paintEvent(QPaintEvent *event)
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

    void onItemClickedDirect()
    {
        std::stack<FluVNavigationIconTextItem *> itemStack;
        FluVNavigationIconTextItem *item = this;
        itemStack.push(item);
        while (item->m_parentItem != nullptr)
        {
            item = item->m_parentItem;
            itemStack.push(item);
        }

        if (itemStack.empty())
        {
            return;
        }

        auto topItem = itemStack.top();
        if (!topItem->isLong())
            return;

        while (!itemStack.empty())
        {
            auto item = itemStack.top();
            if ((item->m_bDown && !item->getItems().empty()) || item->getItems().empty())
                item->onItemClicked();
            itemStack.pop();
        }
    }

    void onThemeChanged()
    {
        m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluThemeUtils::getUtils()->getTheme()));
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluThemeUtils::getUtils()->getTheme()));
        FluStyleSheetUitls::setQssByFileName("FluVNavigationIconTextItem.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    QWidget *m_wrapWidget1;
    QWidget *m_wrapWidget2;

    QWidget *m_emptyWidget;

    QWidget *m_indicator;
    QPushButton *m_iconBtn;
    QLabel *m_label;
    QPushButton *m_arrow;
    QHBoxLayout *m_hLayout1;
    std::vector<FluVNavigationIconTextItem *> m_items;

    QVBoxLayout *m_vMainLayout;
    QVBoxLayout *m_vLayout1;

    FluVNavigationIconTextItem *m_parentItem;

    FluAwesomeType m_awesomeType;  // the icon display which

    bool m_bHideIcon;
    bool m_bDown;
    bool m_bLong;
    bool m_bSelected;
    bool m_bEnableThisItem;
};
