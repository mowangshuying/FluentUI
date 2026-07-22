#include "FluVNavigationIconTextItem.h"
#include "FluVNavigationMenuItem.h"
#include <QStyle>
#include "../Utils/FluUtils.h"
#include "FluVNavigationView.h"
#include "FluVNavigationFlyIconTextItem.h"
#include <QThread>

FluVNavigationIconTextItem::FluVNavigationIconTextItem(QWidget *parent /*= nullptr*/) : FluVNavigationItem(parent)
{
    m_itemType = FluVNavigationItemType::IconText;
    m_isHideIcon = false;
setFixedSize(180, 30);
    m_wrapWidget1 = new QWidget(this);
    m_wrapWidget2 = new QWidget(this);

    m_wrapWidget1->setObjectName("wrapWidget1");
    m_wrapWidget2->setObjectName("wrapWidget2");

    m_isSelected = false;
    m_wrapWidget1->setProperty("selected", false);
    setProperty("selected", false);

    m_emptyWidget = new QWidget(this);
    m_emptyWidget->setFixedSize(0, 0);
    // m_emptyWidget->hide();

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(2);
    m_mainLayout->addWidget(m_wrapWidget1);
    m_mainLayout->addWidget(m_wrapWidget2);
    m_wrapWidget2->hide();

    m_horizontalLayout1 = new QHBoxLayout(m_wrapWidget1);
    m_wrapWidget1->setFixedSize(180, 30);
    //  m_mainLayout->addWidget(m_wrapWidget1);

    m_verticalLayout1 = new QVBoxLayout(m_wrapWidget2);
    m_horizontalLayout1->setContentsMargins(4, 3, 4, 3);
    m_indicator = new FluVNavigationIndicator(this);
    m_iconButton = new QPushButton(this);
    m_label = new QLabel("Home");
    m_label->setWordWrap(false);
    m_arrow = new QPushButton(this);

    m_horizontalLayout1->setSpacing(0);
    // m_horizontalLayout1->addSpacing(4);
    m_horizontalLayout1->addWidget(m_emptyWidget);
    m_horizontalLayout1->addWidget(m_indicator);
    m_horizontalLayout1->addWidget(m_iconButton);
    m_horizontalLayout1->addSpacing(12);
    m_horizontalLayout1->addWidget(m_label, 1);
    m_horizontalLayout1->addWidget(m_arrow);
    //  m_horizontalLayout1->addSpacing(4);

    // m_horizontalLayout1->setSpacing(0);

    m_iconButton->setFixedSize(24, 24);
    // m_label->setWordWrap(true);

    m_verticalLayout1->setContentsMargins(0, 0, 0, 0);
    m_verticalLayout1->setSpacing(2);
    m_iconButton->setObjectName("icon");
    m_label->setObjectName("label");
    m_arrow->setObjectName("arrow");

    m_iconButton->setIconSize(QSize(20, 20));
    m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Home, FluThemeUtils::getUtils()->getTheme()));

    m_arrow->setIconSize(QSize(16, 16));
    m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluThemeUtils::getUtils()->getTheme()));
    m_arrow->setFixedWidth(20);
    m_isDown = true;
    m_isLong = true;
    m_arrow->hide();

    m_isEnableThisItem = true;
    m_awesomeType = FluAwesomeType::None;
    //  QString qss = FluStyleSheetUtils::getQssByFileName("../StyleSheet/light/FluNavigationIconTextItem.qss");
    //  setStyleSheet(qss);

    // m_currentWidth  = 320;
    m_parentItem = nullptr;
    m_parentView = nullptr;

    setState(FluVNavigationState::Collapsed);
    connect(m_arrow, &QPushButton::clicked, this, [=](bool b) { emit itemClicked(); });
    connect(m_iconButton, &QPushButton::clicked, this, [=](bool b) { emit itemClicked(); });
    connect(this, &FluVNavigationIconTextItem::itemClicked, this, [=]() { onItemClicked(); });

    onThemeChanged();
}

FluVNavigationIconTextItem::FluVNavigationIconTextItem(QIcon icon, QString text, QWidget *parent /*= nullptr*/) : FluVNavigationIconTextItem(parent)
{
    m_iconButton->setIcon(icon);
    m_label->setText(text);
}

FluVNavigationIconTextItem::FluVNavigationIconTextItem(QString text, QWidget *parent /*= nullptr*/) : FluVNavigationIconTextItem(parent)
{
    m_iconButton->hide();
    m_isHideIcon = true;
    m_label->setText(text);
}

FluVNavigationIconTextItem::FluVNavigationIconTextItem(FluAwesomeType awesomeType, QString text, QWidget *parent /*= nullptr*/) : FluVNavigationIconTextItem(parent)
{
    m_awesomeType = awesomeType;
    m_iconButton->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluThemeUtils::getUtils()->getTheme()));
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
    m_iconButton->setIcon(item->getIconButton()->icon());
    m_label->setText(item->getLabel()->text());
    m_awesomeType = item->getAwesomeType();

    m_isHideIcon = item->getHideIcon();
    m_key = item->getKey();
    if (m_isHideIcon)
        m_iconButton->hide();

    std::vector<FluVNavigationIconTextItem *> items = item->getItems();
    for (auto tmpItem : items)
    {
        auto newItem = new FluVNavigationIconTextItem;
        newItem->itemClone(tmpItem);
        addItem(newItem);
    }
}

void FluVNavigationIconTextItem::setItemWidth(int width)
{
    // set child item width
    for (auto item : m_items)
    {
        // item->getWrapWidget1()->setFixedWidth(width);
        // item->getWrapWidget2()->setFixedWidth(width);
        // item->setFixedWidth(width);
        item->setItemWidth(width);
    }

    // set self width
    m_wrapWidget1->setFixedWidth(width);
    m_wrapWidget2->setFixedWidth(width);
    setFixedWidth(width);
}

void FluVNavigationIconTextItem::setItemHeight(int height)
{
    int itemHeight = height - m_mainLayout->contentsMargins().top() - m_mainLayout->contentsMargins().bottom();
    for (auto item : m_items)
    {
        item->setItemHeight(height);
    }

    m_wrapWidget1->setFixedHeight(itemHeight);
    m_wrapWidget2->setFixedHeight(itemHeight);
    setFixedHeight(height);
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
    m_verticalLayout1->addWidget(item);
    m_arrow->show();
}

int FluVNavigationIconTextItem::calcItemW1Width()
{
    QMargins margins = m_horizontalLayout1->contentsMargins();
    int indicatorWidth = m_indicator->width();

    int iconWidth = m_iconButton->width();
    if (m_isHideIcon)
        iconWidth = 0;

    int spacing = 12;
    // m_label->show();
    int labelWidth = m_label->fontMetrics().horizontalAdvance(m_label->text());
    int arrowWidth = m_arrow->width();

    if (m_items.empty())
        arrowWidth = 0;

    // LOG_DEBUG << "Text:" << m_label->text() << "==========================================";
    // LOG_DEBUG << "margins left:" << margins.left() << ",margins right:" << margins.right();
    // LOG_DEBUG << "indicatorWidth:" << indicatorWidth;
    // LOG_DEBUG << "iconWidth:" << iconWidth;
    // LOG_DEBUG << "spacing:" << spacing;
    // LOG_DEBUG << "labelWidth:" << labelWidth;
    // LOG_DEBUG << "arrowWidth:" << arrowWidth;
    // LOG_DEBUG << "getDepth:" << getDepth();

    int curentWidth = margins.left() + indicatorWidth + iconWidth + spacing + labelWidth + arrowWidth + margins.right() + 32 * getDepth();
    // LOG_DEBUG << "W1 width:" << curentWidth;
    return curentWidth;
}

int FluVNavigationIconTextItem::calcItemWidth()
{
    int currentWidth = calcItemW1Width();
    int layoutCount = m_verticalLayout1->count();

    for (int i = 0; i < layoutCount; i++)
    {
        if (getState() != FluVNavigationState::Expanded && getState() != FluVNavigationState::Expanding)
        {
            break;
        }
        auto tmpItem = (FluVNavigationIconTextItem *)m_verticalLayout1->itemAt(i)->widget();
        int tmpWidth = tmpItem->calcItemW1Width();
        if (tmpWidth > currentWidth)
            currentWidth = tmpWidth;
    }

    if (getState() == FluVNavigationState::Expanded)
        currentWidth = qMax(width(), currentWidth);

    return currentWidth;
}

int FluVNavigationIconTextItem::calcItemW2Height(FluVNavigationIconTextItem *item)
{
    int h = 0;
    int layoutCount = item->m_verticalLayout1->count();
    for (int i = 0; i < layoutCount; i++)
    {
        auto tmpItem = (FluVNavigationIconTextItem *)item->m_verticalLayout1->itemAt(i)->widget();
        h += tmpItem->height();
    }
    h = h + 2 * (layoutCount - 1) + m_verticalLayout1->contentsMargins().top() + m_verticalLayout1->contentsMargins().bottom();
    return h;
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
    int maxWidth = calcItemWidth();
    item->setItemWidth(maxWidth);
    adjustItemWidth(item->m_parentItem);
}

void FluVNavigationIconTextItem::adjustItemHeight(FluVNavigationIconTextItem *item)
{
    if (item == nullptr)
    {
        return;
    }

    int h = calcItemW2Height(item);
    item->m_wrapWidget2->setFixedHeight(h);
    item->setFixedHeight(item->m_wrapWidget1->height() + item->m_wrapWidget2->height() + m_mainLayout->spacing() + m_mainLayout->contentsMargins().top() + m_mainLayout->contentsMargins().bottom());
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
    int depth = 0;
    FluVNavigationIconTextItem *item = m_parentItem;
    while (item != nullptr)
    {
        depth++;
        item = item->m_parentItem;
    }
    return depth;
}

void FluVNavigationIconTextItem::updateDepth(FluVNavigationIconTextItem *item)
{
    if (item == nullptr)
        return;

    int depth = item->getDepth();
    item->m_emptyWidget->setFixedWidth(32 * depth);

    // get sub items and update depth
    for (auto tmpItem : item->getItems())
    {
        tmpItem->m_emptyWidget->setFixedWidth(32 * tmpItem->getDepth());
        updateDepth(tmpItem);
    }
}

FluVNavigationIconTextItem *FluVNavigationIconTextItem::getRootItem()
{
    int depth = 0;
    FluVNavigationIconTextItem *item = this;
    while (item->m_parentItem != nullptr)
    {
        // depth++;
        item = item->m_parentItem;
    }
    return item;
}

void FluVNavigationIconTextItem::clearItemsSelectState(FluVNavigationIconTextItem *item)
{
    if (item == nullptr)
        return;

    item->m_isSelected = false;
    item->setProperty("selected", false);
    item->m_wrapWidget1->setProperty("selected", false);
    item->m_indicator->setSelected(false);
    for (int i = 0; i < item->m_verticalLayout1->count(); i++)
    {
        auto tmpItem = (FluVNavigationIconTextItem *)item->m_verticalLayout1->itemAt(i)->widget();
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
    item->m_iconButton->style()->polish(item->m_iconButton);
    item->m_label->style()->polish(item->m_label);
    item->m_arrow->style()->polish(item->m_arrow);

    for (int i = 0; i < item->m_verticalLayout1->count(); i++)
    {
        auto tmpItem = (FluVNavigationIconTextItem *)item->m_verticalLayout1->itemAt(i)->widget();
        updateItemsStyleSheet(tmpItem);
    }
}

void FluVNavigationIconTextItem::updateSelected(bool b)
{
    m_isSelected = b;
    setProperty("selected", b);
    m_wrapWidget1->setProperty("selected", b);
    m_indicator->setSelected(b);
    m_label->setProperty("selected", b);
}

void FluVNavigationIconTextItem::enableThisItem(bool b)
{
    m_isEnableThisItem = b;
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
    if (!m_isEnableThisItem)
        return;

    // LOG_DEBUG << "enable this item.";
    //  get root item
    auto rootItem = getRootItem();
    if (rootItem == nullptr)
        return;

    LOG_WARN << "get root item.";
    auto navView = rootItem->getParentView();
    auto flyItem = rootItem->getFlyItem();
    // LOG_WARN << "isDown:" << m_isDown << "nav long:" << navView->isLong();

    if ((navView != nullptr && m_isDown && navView->isLong()) || (navView == nullptr && isLong() && m_isDown))
    {
        setState(FluVNavigationState::Expanding);
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronUp, FluThemeUtils::getUtils()->getTheme()));

        // adjust height ---
        // display child
        if (m_items.size() > 0)
        {
            int h = 0;
            int layout1Count = m_verticalLayout1->count();
            for (int i = 0; i < layout1Count; i++)
            {
                auto item = (FluVNavigationIconTextItem *)m_verticalLayout1->itemAt(i)->widget();
                h += item->height();
            }
            h = h + m_verticalLayout1->spacing() * (layout1Count - 1) + m_verticalLayout1->contentsMargins().top() + m_verticalLayout1->contentsMargins().bottom();
            m_wrapWidget2->setFixedHeight(h);
            m_wrapWidget2->show();
            setFixedHeight(m_wrapWidget1->height() + m_wrapWidget2->height() + m_mainLayout->contentsMargins().top() + m_mainLayout->contentsMargins().bottom() + m_mainLayout->spacing());
        }

        adjustItemHeight(m_parentItem);
        adjustFlyItemHeight(getFlyItem());

        // adjust width
        if (flyItem != nullptr)
        {
            if (getState() == FluVNavigationState::Expanding)
            {
                // int maxW = calcItemWidth();
                // for (int i = 0; i < m_verticalLayout1->count(); i++)
                //{
                //     auto tmpItem = (FluVNavigationIconTextItem *)m_verticalLayout1->itemAt(i)->widget();
                //     tmpItem->getWrapWidget1()->setFixedWidth(maxW);
                //     tmpItem->getWrapWidget2()->setFixedWidth(maxW);
                //     tmpItem->setFixedWidth(maxW);
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

    if ((navView != nullptr && !m_isDown && navView->isLong()) || (navView == nullptr && isLong() && !m_isDown))
    {
        setState(FluVNavigationState::Collapsing);
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluThemeUtils::getUtils()->getTheme()));
        setFixedHeight(30);
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

    m_isDown = !m_isDown;
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
