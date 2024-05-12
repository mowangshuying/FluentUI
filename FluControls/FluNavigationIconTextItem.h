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
#include <QWidget>
#include "FluNavigationItem.h"
#include "../FluUtils/FluUtils.h"
#include <stack>

class FluNavigationView;
class FluNavigationIconTextItem : public FluNavigationItem
{
    Q_OBJECT
  public:
    FluNavigationIconTextItem(QWidget *parent = nullptr);

    FluNavigationIconTextItem(QIcon icon, QString text, QWidget *parent = nullptr);

    FluNavigationIconTextItem(FluAwesomeType awesomeType, QString text, QWidget *parent = nullptr);

    FluNavigationIconTextItem(QString text, QWidget *parent = nullptr);

    FluNavigationIconTextItem(FluNavigationIconTextItem *item);

    void copyItem(FluNavigationIconTextItem* item);

    QWidget *getWrapWidget1()
    {
        return m_wrapWidget1;
    }

    QWidget *getWrapWidget2()
    {
        return m_wrapWidget2;
    }

    QPushButton* getIconBtn()
    {
        return m_iconBtn;
    }

    QLabel* getLabel()
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

    std::vector<FluNavigationIconTextItem *> getChildItems();
    void getAllItems(std::vector<FluNavigationIconTextItem *> &totalItems)
    {
        std::vector<FluNavigationIconTextItem *> childItems = getChildItems();
        for (auto childItem : childItems)
        {
            totalItems.push_back(childItem);
            childItem->getAllItems(totalItems);
        }
    }

    void addItem(FluNavigationIconTextItem *item);

    int calcItemW1Width();
    int calcItemW2Height(FluNavigationIconTextItem *item);

    void adjustItemHeight(FluNavigationIconTextItem *item);

    int getDepth();

    FluNavigationIconTextItem *getRootItem();

    void clearAllItemsSelectState()
    {
        FluNavigationIconTextItem *rootItem = getRootItem();
        clearItemsSelectState(rootItem);
    }

    void clearItemsSelectState(FluNavigationIconTextItem *item);

    void updateAllItemsStyleSheet()
    {
        FluNavigationIconTextItem *rootItem = getRootItem();
        updateItemsStyleSheet(rootItem);
    }

    void updateItemsStyleSheet(FluNavigationIconTextItem *item);

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
        std::stack<FluNavigationIconTextItem *> itemStack;
        FluNavigationIconTextItem *item = this;
        itemStack.push(item);
        while (item->m_parentItem != nullptr)
        {
            item = item->m_parentItem;
            itemStack.push(item);
        }

        while (!itemStack.empty())
        {
            auto item = itemStack.top();
            if ((item->m_bDown && !item->getChildItems().empty()) || item->getChildItems().empty())
                item->onItemClicked();
            itemStack.pop();
        }
    }

    void onThemeChanged()
    {
        // LOG_DEBUG << "called";
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, QColor(8, 8, 8)));
            m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, QColor(8, 8, 8)));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNavigationIconTextItem.qss", this);
        }
        else
        {
            m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, QColor(239, 239, 239)));
            m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, QColor(239, 239, 239)));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluNavigationIconTextItem.qss", this);
        }
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
    std::vector<FluNavigationIconTextItem *> m_items;

    QVBoxLayout *m_vMainLayout;
    QVBoxLayout *m_vLayout1;

    FluNavigationIconTextItem *m_parentItem;

    FluAwesomeType m_awesomeType;  // the icon display which

    bool m_bHideIcon;
    bool m_bDown;
    bool m_bLong;
    bool m_bSelected;
    bool m_bEnableThisItem;
};
