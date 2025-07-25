﻿#include "FluVNavigationIconTextItem.h"
#include "FluVNavigationMenuItem.h"
#include <QStyle>
#include "../FluUtils/FluUtils.h"
#include "FluVNavigationView.h"
#include "FluVNavigationFlyIconTextItem.h"
#include <QThread>

FluVNavigationIconTextItem::FluVNavigationIconTextItem(QWidget *parent /*= nullptr*/) : FluVNavigationItem(parent)
{
    m_itemType = FluVNavigationItemType::IconText;
    m_bHideIcon = false;
    setFixedSize(320, 40);
    m_wrapWidget1 = new QWidget(this);
    m_wrapWidget2 = new QWidget(this);

    m_wrapWidget1->setObjectName("wrapWidget1");
    m_wrapWidget2->setObjectName("wrapWidget2");

    m_bSelected = false;
    m_wrapWidget1->setProperty("selected", false);
    setProperty("selected", false);

    m_emptyWidget = new QWidget(this);
    m_emptyWidget->setFixedSize(0, 0);
    // m_emptyWidget->hide();

    m_vMainLayout = new QVBoxLayout(this);
    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    m_vMainLayout->setSpacing(5);
    m_vMainLayout->addWidget(m_wrapWidget1);
    m_vMainLayout->addWidget(m_wrapWidget2);
    m_wrapWidget2->hide();

    m_hLayout1 = new QHBoxLayout(m_wrapWidget1);
    m_wrapWidget1->setFixedSize(320, 40);
    //  m_vMainLayout->addWidget(m_wrapWidget1);

    m_vLayout1 = new QVBoxLayout(m_wrapWidget2);
    m_hLayout1->setContentsMargins(4, 4, 4, 4);
    m_indicator = new QWidget(this);
    m_iconBtn = new QPushButton(this);
    m_label = new QLabel("Home");
    m_label->setWordWrap(false);
    m_arrow = new QPushButton(this);

    m_hLayout1->setSpacing(0);
    // m_hLayout1->addSpacing(4);
    m_hLayout1->addWidget(m_emptyWidget);
    m_hLayout1->addWidget(m_indicator);
    m_hLayout1->addWidget(m_iconBtn);
    m_hLayout1->addSpacing(8);
    m_hLayout1->addWidget(m_label, 1);
    m_hLayout1->addWidget(m_arrow);
    //  m_hLayout1->addSpacing(4);

    // m_hLayout1->setSpacing(0);

    m_indicator->setFixedHeight(18);
    m_indicator->setFixedWidth(4);
    m_iconBtn->setFixedSize(30, 30);
    // m_label->setWordWrap(true);

    m_vLayout1->setContentsMargins(0, 0, 0, 0);
    m_vLayout1->setSpacing(5);
    m_indicator->setObjectName("indicator");
    m_iconBtn->setObjectName("icon");
    m_label->setObjectName("label");
    m_arrow->setObjectName("arrow");

    m_iconBtn->setIconSize(QSize(24, 24));
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Home, FluThemeUtils::getUtils()->getTheme()));

    m_arrow->setIconSize(QSize(18, 18));
    m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluThemeUtils::getUtils()->getTheme()));
    m_arrow->setFixedWidth(25);
    m_bDown = true;
    m_bLong = true;
    m_arrow->hide();

    m_bEnableThisItem = true;
    m_awesomeType = FluAwesomeType::None;
    //  QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluNavigationIconTextItem.qss");
    //  setStyleSheet(qss);

    // m_currentWidth  = 320;
    m_parentItem = nullptr;
    m_parentView = nullptr;

    setState(FluVNavigationState::Collapsed);
    connect(m_arrow, &QPushButton::clicked, this, [=](bool b) { emit itemClicked(); });
    connect(m_iconBtn, &QPushButton::clicked, this, [=](bool b) { emit itemClicked(); });
    connect(this, &FluVNavigationIconTextItem::itemClicked, this, [=]() { onItemClicked(); });

    onThemeChanged();
}

FluVNavigationIconTextItem::FluVNavigationIconTextItem(QIcon icon, QString text, QWidget *parent /*= nullptr*/) : FluVNavigationIconTextItem(parent)
{
    m_iconBtn->setIcon(icon);
    m_label->setText(text);
}

FluVNavigationIconTextItem::FluVNavigationIconTextItem(QString text, QWidget *parent /*= nullptr*/) : FluVNavigationIconTextItem(parent)
{
    m_iconBtn->hide();
    m_bHideIcon = true;
    m_label->setText(text);
}

FluVNavigationIconTextItem::FluVNavigationIconTextItem(FluAwesomeType awesomeType, QString text, QWidget *parent /*= nullptr*/) : FluVNavigationIconTextItem(parent)
{
    m_awesomeType = awesomeType;
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluThemeUtils::getUtils()->getTheme()));
    m_label->setText(text);
}

FluVNavigationIconTextItem::FluVNavigationIconTextItem(FluVNavigationIconTextItem *item, QWidget *parent /*= nullptr*/) : FluVNavigationIconTextItem(parent)
{
    itemClone(item);
    onThemeChanged();
}

void FluVNavigationIconTextItem::itemClone(FluVNavigationIconTextItem *item)
{
    // LOG_DEBUG << "Clone Item:" << item->getLabel()->text();
    m_iconBtn->setIcon(item->getIconBtn()->icon());
    m_label->setText(item->getLabel()->text());
    m_awesomeType = item->getAwesomeType();

    m_bHideIcon = item->getHideIcon();
    m_key = item->getKey();
    if (m_bHideIcon)
        m_iconBtn->hide();

    std::vector<FluVNavigationIconTextItem *> items = item->getItems();
    for (auto tmpItem : items)
    {
        auto newItem = new FluVNavigationIconTextItem;
        newItem->itemClone(tmpItem);
        addItem(newItem);
    }
}

void FluVNavigationIconTextItem::setItemWidth(int nWidth)
{
    // set child item width
    for (auto item : m_items)
    {
        item->getWrapWidget1()->setFixedWidth(nWidth);
        item->getWrapWidget2()->setFixedWidth(nWidth);
        item->setFixedWidth(nWidth);
    }

    // set self width
    m_wrapWidget1->setFixedWidth(nWidth);
    m_wrapWidget2->setFixedWidth(nWidth);
    setFixedWidth(nWidth);
}

std::vector<FluVNavigationIconTextItem *> FluVNavigationIconTextItem::getItems()
{
    return m_items;
}

void FluVNavigationIconTextItem::getAllItems(std::vector<FluVNavigationIconTextItem *> &totalItems)
{
    std::vector<FluVNavigationIconTextItem *> childItems = getItems();
    for (auto childItem : childItems)
    {
        totalItems.push_back(childItem);
        childItem->getAllItems(totalItems);
    }
}

std::vector<FluVNavigationIconTextItem *> FluVNavigationIconTextItem::getAllItems()
{
    std::vector<FluVNavigationIconTextItem *> totalItems;
    getAllItems(totalItems);
    return totalItems;
}

void FluVNavigationIconTextItem::addItem(FluVNavigationIconTextItem *item)
{
    item->m_parentItem = this;
    m_items.push_back(item);
    updateDepth(item);
    m_vLayout1->addWidget(item);
    m_arrow->show();
}

int FluVNavigationIconTextItem::calcItemW1Width()
{
    QMargins margins = m_hLayout1->contentsMargins();
    int nIndicatorWidth = m_indicator->width();

    int nIconWidth = m_iconBtn->width();
    if (m_bHideIcon)
        nIconWidth = 0;

    int nSpacing = 8;
    // m_label->show();
    int nLabelWidth = m_label->fontMetrics().horizontalAdvance(m_label->text());
    int nArrowWidth = m_arrow->width();

    if (m_items.empty())
        nArrowWidth = 0;

    // LOG_DEBUG << "Text:" << m_label->text() << "==========================================";
    // LOG_DEBUG << "margins left:" << margins.left() << ",margins right:" << margins.right();
    // LOG_DEBUG << "nIndicatorWidth:" << nIndicatorWidth;
    // LOG_DEBUG << "nIconWidth:" << nIconWidth;
    // LOG_DEBUG << "nSpacing:" << nSpacing;
    // LOG_DEBUG << "nLabelWidth:" << nLabelWidth;
    // LOG_DEBUG << "nArrowWidth:" << nArrowWidth;
    // LOG_DEBUG << "getDepth:" << getDepth();

    int nCurentWidth = margins.left() + nIndicatorWidth + nIconWidth + nSpacing + nLabelWidth + nArrowWidth + margins.right() + 36 * getDepth();
    // LOG_DEBUG << "W1 width:" << nCurentWidth;
    return nCurentWidth;
}

int FluVNavigationIconTextItem::calcItemWidth()
{
    int nCurrentWidth = calcItemW1Width();
    int nLayoutCount = m_vLayout1->count();

    for (int i = 0; i < nLayoutCount; i++)
    {
        if (getState() != FluVNavigationState::Expanded && getState() != FluVNavigationState::Expanding)
        {
            break;
        }
        auto tmpItem = (FluVNavigationIconTextItem *)m_vLayout1->itemAt(i)->widget();
        int nTmpWidth = tmpItem->calcItemW1Width();
        if (nTmpWidth > nCurrentWidth)
            nCurrentWidth = nTmpWidth;
    }

    if (getState() == FluVNavigationState::Expanded)
        nCurrentWidth = qMax(width(), nCurrentWidth);

    return nCurrentWidth;
}

int FluVNavigationIconTextItem::calcItemW2Height(FluVNavigationIconTextItem *item)
{
    int nH = 0;
    int nLayoutCount = item->m_vLayout1->count();
    for (int i = 0; i < nLayoutCount; i++)
    {
        auto tmpItem = (FluVNavigationIconTextItem *)item->m_vLayout1->itemAt(i)->widget();
        nH += tmpItem->height();
    }
    nH = nH + 5 * (nLayoutCount - 1) + m_vLayout1->contentsMargins().top() + m_vLayout1->contentsMargins().bottom();
    return nH;
}

void FluVNavigationIconTextItem::adjustItemWidth()
{
    adjustItemWidth(this);
}
void FluVNavigationIconTextItem::adjustItemWidth(FluVNavigationIconTextItem *item)
{
    if (item == nullptr)
    {
        return;
    }

    // LOG_DEBUG << "item:" << item->getLabel();
    int nMaxWidth = calcItemWidth();
    item->setItemWidth(nMaxWidth);
    adjustItemWidth(item->m_parentItem);
}

void FluVNavigationIconTextItem::adjustItemHeight(FluVNavigationIconTextItem *item)
{
    if (item == nullptr)
    {
        return;
    }

    int nH = calcItemW2Height(item);
    item->m_wrapWidget2->setFixedHeight(nH);
    item->setFixedHeight(item->m_wrapWidget1->height() + item->m_wrapWidget2->height() + m_vMainLayout->spacing() + m_vMainLayout->contentsMargins().top() + m_vMainLayout->contentsMargins().bottom());
    adjustItemHeight(item->m_parentItem);
}

void FluVNavigationIconTextItem::adjustFlyItemHeight(FluVNavigationFlyIconTextItem *flyItem)
{
    if (flyItem == nullptr)
        return;

    flyItem->adjustItemHeight();
}

void FluVNavigationIconTextItem::adjustFlyItemWidth(FluVNavigationFlyIconTextItem *flyItem)
{
    if (flyItem == nullptr)
        return;
    flyItem->adjustItemWidth();
}

int FluVNavigationIconTextItem::getDepth()
{
    int nDepth = 0;
    FluVNavigationIconTextItem *item = m_parentItem;
    while (item != nullptr)
    {
        nDepth++;
        item = item->m_parentItem;
    }
    return nDepth;
}

void FluVNavigationIconTextItem::updateDepth(FluVNavigationIconTextItem *item)
{
    if (item == nullptr)
        return;

    int nDepth = item->getDepth();
    item->m_emptyWidget->setFixedWidth(36 * nDepth);

    // get sub items and update depth
    for (auto tmpItem : item->getItems())
    {
        tmpItem->m_emptyWidget->setFixedWidth(36 * tmpItem->getDepth());
        updateDepth(tmpItem);
    }
}

FluVNavigationIconTextItem *FluVNavigationIconTextItem::getRootItem()
{
    int nDepth = 0;
    FluVNavigationIconTextItem *item = this;
    while (item->m_parentItem != nullptr)
    {
        // nDepth++;
        item = item->m_parentItem;
    }
    return item;
}

void FluVNavigationIconTextItem::clearItemsSelectState(FluVNavigationIconTextItem *item)
{
    if (item == nullptr)
        return;

    item->m_bSelected = false;
    item->setProperty("selected", false);
    item->m_wrapWidget1->setProperty("selected", false);
    item->m_indicator->setProperty("selected", false);
    for (int i = 0; i < item->m_vLayout1->count(); i++)
    {
        auto tmpItem = (FluVNavigationIconTextItem *)item->m_vLayout1->itemAt(i)->widget();
        clearItemsSelectState(tmpItem);
    }
}

void FluVNavigationIconTextItem::updateItemsStyleSheet(FluVNavigationIconTextItem *item)
{
    if (item == nullptr)
        return;

    item->style()->polish(item);
    item->m_wrapWidget1->style()->polish(item->m_wrapWidget1);
    item->m_wrapWidget2->style()->polish(item->m_wrapWidget2);
    item->m_indicator->style()->polish(item->m_indicator);
    item->m_iconBtn->style()->polish(item->m_iconBtn);
    item->m_label->style()->polish(item->m_label);
    item->m_arrow->style()->polish(item->m_arrow);

    for (int i = 0; i < item->m_vLayout1->count(); i++)
    {
        auto tmpItem = (FluVNavigationIconTextItem *)item->m_vLayout1->itemAt(i)->widget();
        updateItemsStyleSheet(tmpItem);
    }
}

void FluVNavigationIconTextItem::updateSelected(bool b)
{
    m_bSelected = b;
    setProperty("selected", b);
    m_wrapWidget1->setProperty("selected", b);
    m_indicator->setProperty("selected", b);
    m_label->setProperty("selected", b);
}

void FluVNavigationIconTextItem::enableThisItem(bool b)
{
    m_bEnableThisItem = b;
    setProperty("enableThisItem", b);
    m_wrapWidget1->setProperty("enableThisItem", b);
    m_indicator->setProperty("enableThisItem", b);
    m_label->setProperty("enableThisItem", b);
}

void FluVNavigationIconTextItem::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    if (!m_wrapWidget1->rect().contains(pos))
        return;

    emit itemClicked();
}

void FluVNavigationIconTextItem::onItemClicked()
{
    LOG_WARN << "called";
    //  enableThisItem equal false just return it.
    if (!m_bEnableThisItem)
        return;

    // LOG_DEBUG << "enable this item.";
    //  get root item
    auto rootItem = getRootItem();
    if (rootItem == nullptr)
        return;

    LOG_WARN << "get root item.";
    auto navView = rootItem->getParentView();
    auto flyItem = rootItem->getFlyItem();
    // LOG_WARN << "bDown:" << m_bDown << "nav long:" << navView->isLong();

    if ((navView != nullptr && m_bDown && navView->isLong()) || (navView == nullptr && isLong() && m_bDown))
    {
        setState(FluVNavigationState::Expanding);
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronUp, FluThemeUtils::getUtils()->getTheme()));

        // adjust height ---
        // display child
        if (m_items.size() > 0)
        {
            int nH = 0;
            int nLayout1Count = m_vLayout1->count();
            for (int i = 0; i < nLayout1Count; i++)
            {
                auto item = (FluVNavigationIconTextItem *)m_vLayout1->itemAt(i)->widget();
                nH += item->height();
            }
            nH = nH + m_vLayout1->spacing() * (nLayout1Count - 1) + m_vLayout1->contentsMargins().top() + m_vLayout1->contentsMargins().bottom();
            m_wrapWidget2->setFixedHeight(nH);
            m_wrapWidget2->show();
            setFixedHeight(m_wrapWidget1->height() + m_wrapWidget2->height() + m_vMainLayout->contentsMargins().top() + m_vMainLayout->contentsMargins().bottom() + m_vMainLayout->spacing());
        }

        adjustItemHeight(m_parentItem);
        adjustFlyItemHeight(getFlyItem());

        // adjust width
        if (flyItem != nullptr)
        {
            if (getState() == FluVNavigationState::Expanding)
            {
                // int nMaxW = calcItemWidth();
                // for (int i = 0; i < m_vLayout1->count(); i++)
                //{
                //     auto tmpItem = (FluVNavigationIconTextItem *)m_vLayout1->itemAt(i)->widget();
                //     tmpItem->getWrapWidget1()->setFixedWidth(nMaxW);
                //     tmpItem->getWrapWidget2()->setFixedWidth(nMaxW);
                //     tmpItem->setFixedWidth(nMaxW);
                // }
                // adjustItemWidth(m_parentItem);

                if (getLabel()->text() == tr("3-level"))
                {
                    QThread::sleep(1);
                }

                adjustItemWidth();
                adjustFlyItemWidth(getFlyItem());
            }
        }
        m_wrapWidget2->show();

        setState(FluVNavigationState::Expanded);
    }

    if ((navView != nullptr && !m_bDown && navView->isLong()) || (navView == nullptr && isLong() && !m_bDown))
    {
        setState(FluVNavigationState::Collapsing);
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluThemeUtils::getUtils()->getTheme()));
        setFixedHeight(40);
        if (m_items.size() > 0)
        {
            m_wrapWidget2->hide();
            adjustItemHeight(m_parentItem);
            adjustFlyItemHeight(getFlyItem());
            adjustFlyItemWidth(getFlyItem());
        }
        setState(FluVNavigationState::Collapsed);
    }

    if (navView != nullptr && !navView->isLong() && rootItem == this)
    {
        if (!getItems().empty())
        {
            QPoint gPoint = mapToGlobal(QPoint(navView->width(), 0));
            auto flyIconTextItem = new FluVNavigationFlyIconTextItem;
            flyIconTextItem->setIconTextItems(getItems());
            flyIconTextItem->move(gPoint.x(), gPoint.y());
            flyIconTextItem->show();
        }
    }

    if (navView != nullptr && !navView->isLong())
    {
        navView->clearAllItemsSelectState();
        rootItem->updateSelected(true);
        navView->updateAllItemsStyleSheet();
        return;
    }

    m_bDown = !m_bDown;
    if (navView != nullptr)
    {
        navView->clearAllItemsSelectState();  // clear state
        updateSelected(true);
        navView->updateAllItemsStyleSheet();  // update state
    }

    if (navView == nullptr)
    {
        rootItem->clearAllItemsSelectState();
        updateSelected(true);
        rootItem->updateAllItemsStyleSheet();
    }
}
