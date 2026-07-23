#include "FluHNavigationIconTextItem.h"
#include "FluHNavigationFlyIconTextItem.h"
#include <QThread>
#include "FluHNavigationView.h"
#include "FluVScrollView.h"

FluHNavigationIconTextItem::FluHNavigationIconTextItem(QWidget* parent /*= nullptr*/) : FluHNavigationItem(parent)
{
    m_itemType = FluHNavigationItemType::IconText;
    m_parentView = nullptr;
    m_awesomeType = FluAwesomeType::None;
    m_parentItem = nullptr;
    m_isDown = true;
    m_isParentIsFlyIconTextItem = false;
    m_isParentIsNavigationView = false;

    m_isHideIcon = false;
    m_isSelected = false;
    m_parentFlyIconTextItem = nullptr;

    m_wrapWidget1 = new QWidget;
    m_wrapWidget2 = new QWidget;

    m_wrapWidget1->setObjectName("wrapWidget1");
    m_wrapWidget2->setObjectName("wrapWidget2");

    m_horizontalIndicator = new FluHNavigationIndicator;

    m_horizontalIndicatorWrap = new QWidget;
    m_horizontalIndicatorLayout = new QHBoxLayout;
    m_horizontalIndicatorLayout->setContentsMargins(0, 0, 0, 0);
    m_horizontalIndicatorWrap->setFixedHeight(3);
    m_horizontalIndicatorWrap->setLayout(m_horizontalIndicatorLayout);

    m_horizontalIndicatorLayout->addWidget(m_horizontalIndicator, 1);

    m_emptyWidget = new QWidget;
    m_emptyWidget->setFixedSize(0, 0);

    m_mainLayout = new QVBoxLayout;
    setLayout(m_mainLayout);

    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    m_mainLayout->addWidget(m_wrapWidget1);
    m_mainLayout->addWidget(m_wrapWidget2);
    m_mainLayout->addWidget(m_horizontalIndicatorWrap);

    m_wrapWidget2->hide();
    m_horizontalIndicator->setVisible(false);

    m_horizontalLayout1 = new QHBoxLayout;
    m_wrapWidget1->setLayout(m_horizontalLayout1);
    m_horizontalLayout1->setContentsMargins(3, 3, 3, 3);
    m_horizontalLayout1->setSpacing(0);

    m_verticalLayout1 = new QVBoxLayout;
    m_wrapWidget2->setLayout(m_verticalLayout1);

    m_verticalIndicator = new QWidget;
    m_iconButton = new QPushButton;
    m_label = new QLabel;
    m_arrow = new QPushButton;

    m_horizontalLayout1->addWidget(m_emptyWidget);
    m_horizontalLayout1->addWidget(m_verticalIndicator);
    m_horizontalLayout1->addWidget(m_iconButton);
    m_horizontalLayout1->addSpacing(6);
    m_horizontalLayout1->addWidget(m_label, 1);
    m_horizontalLayout1->addWidget(m_arrow);

    m_verticalIndicator->setFixedHeight(18);
    m_verticalIndicator->setFixedWidth(4);

    m_verticalLayout1->setContentsMargins(0, 0, 0, 0);
    m_verticalLayout1->setSpacing(0);

    // set obj names;
    m_verticalIndicator->setObjectName("indicator");
    m_iconButton->setObjectName("icon");
    m_label->setObjectName("label");
    m_arrow->setObjectName("arrow");

    m_iconButton->setIconSize(QSize(18, 18));
    m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::None, FluThemeUtils::getUtils()->getTheme()));
    m_iconButton->setFixedSize(22, 22);

    m_arrow->setIconSize(QSize(14, 14));
    m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::None, FluThemeUtils::getUtils()->getTheme()));
    m_arrow->setFixedWidth(18);

    connect(m_arrow, &QPushButton::clicked, this, [=]() { emit itemClicked(); });
    connect(m_iconButton, &QPushButton::clicked, this, [=]() { emit itemClicked(); });
    connect(this, &FluHNavigationIconTextItem::itemClicked, this, [=]() { onItemClicked(); });

    // fix height 34;
    setFixedHeight(34);
}

FluHNavigationIconTextItem::FluHNavigationIconTextItem(FluAwesomeType awesomeType, QString text, QWidget* parent /*= nullptr*/) : FluHNavigationIconTextItem(parent)
{
    m_awesomeType = awesomeType;
    m_iconButton->setIcon(FluIconUtils::getFluentIcon(m_awesomeType));
    m_label->setText(text);
    m_isHideIcon = false;
    onThemeChanged();
}

FluHNavigationIconTextItem::FluHNavigationIconTextItem(FluHNavigationIconTextItem* item) : FluHNavigationIconTextItem()
{
    itemClone(item);
    onThemeChanged();
}

FluHNavigationIconTextItem::FluHNavigationIconTextItem(QString text, QWidget* parent /*= nullptr*/) : FluHNavigationIconTextItem(parent)
{
    m_awesomeType = FluAwesomeType::None;
    m_iconButton->hide();
    m_isHideIcon = true;

    m_label->setText(text);
    onThemeChanged();
}

FluHNavigationIconTextItem::~FluHNavigationIconTextItem()
{
}

void FluHNavigationIconTextItem::itemClone(FluHNavigationIconTextItem* item)
{
    m_iconButton->setIcon(item->getIconButton()->icon());
    m_label->setText(item->getLabel()->text());
    m_awesomeType = item->getAwesomeType();
    m_key = item->m_key;

    m_isHideIcon = item->getHideIcon();
    if (m_isHideIcon)
        m_iconButton->hide();

    std::vector<FluHNavigationIconTextItem*> items = item->getItems();
    for (auto tmpItem : items)
    {
        auto newItem = new FluHNavigationIconTextItem;
        newItem->itemClone(tmpItem);
        addItem(newItem);
    }
}

void FluHNavigationIconTextItem::getAllItems(std::vector<FluHNavigationIconTextItem*>& totalItems)
{
    std::vector<FluHNavigationIconTextItem*> items = getItems();
    for (auto item : items)
    {
        totalItems.push_back(item);
        item->getAllItems(totalItems);
    }
}

std::vector<FluHNavigationIconTextItem*> FluHNavigationIconTextItem::getAllItems()
{
    std::vector<FluHNavigationIconTextItem*> totalItems;
    getAllItems(totalItems);
    return totalItems;
}

void FluHNavigationIconTextItem::addItem(FluHNavigationIconTextItem* item)
{
    item->m_parentItem = this;
    m_items.push_back(item);

    m_verticalLayout1->addWidget(item);
    setArrowButtonToChevronDown();
}

int FluHNavigationIconTextItem::calcItemW1Width()
{
    QMargins margins = m_wrapWidget1->contentsMargins();
    int leftMargins = margins.left();
    int rightMargins = margins.right();

    int emptyWidgetWidth = m_emptyWidget->width();
    int indicatorWidth = m_verticalIndicator->width();

    int iconWidth = m_iconButton->width();
    if (m_isHideIcon)
    {
        iconWidth = 0;
    }

    int spacing = 8;
    int labelWidth = m_label->fontMetrics().boundingRect(m_label->text()).width();
    int arrowWidth = m_arrow->width();

    // LOG_DEBUG << "Text:" << m_label->text() << "==========================================";
    // LOG_DEBUG << "margins left:" << margins.left() << ",margins right:" << margins.right();
    // LOG_DEBUG << "emptyWidgetWidth:" << emptyWidgetWidth;
    // LOG_DEBUG << "indicatorWidth:" << indicatorWidth;
    // LOG_DEBUG << "iconWidth:" << iconWidth;
    // LOG_DEBUG << "spacing:" << spacing;
    // LOG_DEBUG << "labelWidth:" << labelWidth;
    // LOG_DEBUG << "arrowWidth:" << arrowWidth;
    // LOG_DEBUG << "W1 width:" << leftMargins + emptyWidgetWidth + indicatorWidth + iconWidth + spacing + labelWidth + spacing + arrowWidth + spacing + rightMargins + 20;

    int w1Width = leftMargins + emptyWidgetWidth + indicatorWidth + iconWidth + spacing + labelWidth + arrowWidth + rightMargins + 20;
    // LOG_DEBUG << "item:" << getText() << "W1Width:" << w1Width;
    return w1Width;
}

int FluHNavigationIconTextItem::calcItemWidth()
{
    if (m_isDown || isLeaf())
    {
        return calcItemW1Width();
    }

    int w1Width = calcItemW1Width();
    int w2Width = 0;
    for (int i = 0; i < m_verticalLayout1->layout()->count(); i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(m_verticalLayout1->itemAt(i)->widget());
        int tmpItemWidth = tmpItem->calcItemW1Width();
        if (tmpItemWidth > w2Width)
        {
            w2Width = tmpItemWidth;
        }
    }

    int width = qMax(w1Width, w2Width);
    // LOG_DEBUG << "item:" << getText() << "Width:" << width;
    return width;
}

int FluHNavigationIconTextItem::calcItemW2Height(FluHNavigationIconTextItem* item)
{
    // LOG_DEBUG << "item:" << item->getText() << " "
    //           << "called";
    if (item->getWrapWidget2()->isHidden())
    {
        // LOG_DEBUG << "item:" << item->getText() << " wrap widget2 is hidden.";
        return 0;
    }

    int h = 0;
    for (int i = 0; i < item->m_verticalLayout1->count(); i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(item->m_verticalLayout1->itemAt(i)->widget());
        h += tmpItem->height();
    }

    // LOG_DEBUG << "item:" << item->getText() << " wrap widget2 height:" << h;
    return h;
}

void FluHNavigationIconTextItem::adjustItemHeight(FluHNavigationIconTextItem* item)
{
    if (item == nullptr)
    {
        return;
    }

#ifdef _DEBUG
    // if (item->getText() == "Home")
    // {
    //     QThread::msleep(0);
    // }
#endif
    // LOG_DEBUG << item->getText();
    // LOG_DEBUG << "item:" << item->getText() << "called";

    if (item->m_isDown)
    {
        item->getWrapWidget2()->hide();
    }
    else
    {
        item->getWrapWidget2()->show();
    }

    int h = calcItemW2Height(item);
    item->m_wrapWidget2->setFixedHeight(h);
    item->setFixedHeight(item->m_wrapWidget1->height() + item->m_wrapWidget2->height());

    adjustItemHeight(item->m_parentItem);
    if (item->parentIsFlyIconTextItem())
    {
        auto flyIconTextItem = item->getParentFlyIconTextItem();
        auto vLayout = flyIconTextItem->getVScrollView()->getMainLayout();

        int h = 0;
        for (int i = 0; i < vLayout->count(); i++)
        {
            auto tmpItem = (FluHNavigationIconTextItem*)(vLayout->itemAt(i)->widget());
            h += tmpItem->sizeHint().height();
        }

        // h += 15;
        h += 15;
        if (h > 600)
            h = 600;

        flyIconTextItem->setFixedHeight(h);
        flyIconTextItem->show();
    }
}

void FluHNavigationIconTextItem::adjustItemWidth(FluHNavigationIconTextItem* item, int& maxWidth, int& callHierarchy)
{
    if (item == nullptr)
    {
        return;
    }

    // QString sHierarchy = "";
    // for (int i = 0; i < callHierarchy; i++)
    //{
    //     sHierarchy += "\t";
    // }

    // LOG_DEBUG << sHierarchy << "text:" << getText() << ", child item count:" << item->m_verticalLayout1->count();

    int itemW = item->calcItemWidth();
    if (itemW > maxWidth)
    {
        maxWidth = itemW;
    }

    for (int i = 0; i < item->m_verticalLayout1->count() && !item->m_isDown; i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(item->m_verticalLayout1->itemAt(i)->widget());
        itemW = tmpItem->calcItemWidth();
        if (itemW > maxWidth)
        {
            maxWidth = itemW;
        }
    }

    // LOG_DEBUG << callHierarchy << "max width:" << maxWidth << ","
    //           << "item width:" << itemW;

    item->setItemFixedWidth(maxWidth);
    for (int i = 0; i < item->m_verticalLayout1->count(); i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(item->m_verticalLayout1->itemAt(i)->widget());
        tmpItem->setItemFixedWidth(maxWidth);
    }

    // int callHierarchy = 0;
    adjustItemWidth(item->m_parentItem, maxWidth, callHierarchy);

    if (item->parentIsFlyIconTextItem())
    {
        int maxItemWidth = 0;

        auto vLayout = item->getParentFlyIconTextItem()->getVScrollView()->getMainLayout();
        for (int i = 0; i < vLayout->count(); i++)
        {
            auto tmpItem = (FluHNavigationIconTextItem*)(vLayout->itemAt(i)->widget());
            int tmpWidth = tmpItem->calcItemWidth();
            if (tmpWidth > maxItemWidth)
            {
                maxItemWidth = tmpWidth;
            }
        }

        if (maxItemWidth > maxWidth)
            maxWidth = maxItemWidth;

        for (int i = 0; i < vLayout->count(); i++)
        {
            auto tmpItem = (FluHNavigationIconTextItem*)(vLayout->itemAt(i)->widget());
            tmpItem->setItemFixedWidth(maxWidth);
        }

        item->getParentFlyIconTextItem()->setFixedWidth(maxWidth + 15);
    }
}

void FluHNavigationIconTextItem::setItemFixedWidth(int maxWidth)
{
    setFixedWidth(maxWidth);
    getWrapWidget1()->setFixedWidth(maxWidth);
    getWrapWidget2()->setFixedWidth(maxWidth);

    for (int i = 0; i < m_verticalLayout1->count(); i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(m_verticalLayout1->itemAt(i)->widget());
        tmpItem->setFixedWidth(maxWidth);
        tmpItem->getWrapWidget1()->setFixedWidth(maxWidth);
        tmpItem->getWrapWidget2()->setFixedWidth(maxWidth);
    }
}

void FluHNavigationIconTextItem::setArrowButtonToChevronUp()
{
    if (!m_items.empty())
    {
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronUp, FluThemeUtils::getUtils()->getTheme()));
    }
    else
    {
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::None, FluThemeUtils::getUtils()->getTheme()));
    }
}

void FluHNavigationIconTextItem::setArrowButtonToChevronDown()
{
    if (!m_items.empty())
    {
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluThemeUtils::getUtils()->getTheme()));
    }
    else
    {
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::None, FluThemeUtils::getUtils()->getTheme()));
    }
}

int FluHNavigationIconTextItem::getDepth()
{
    int depth = 0;
    FluHNavigationIconTextItem* item = m_parentItem;
    while (item != nullptr)
    {
        depth++;
        item = item->m_parentItem;
    }
    return depth;
}

FluHNavigationIconTextItem* FluHNavigationIconTextItem::getRootItem()
{
    FluHNavigationIconTextItem* item = this;
    while (item->m_parentItem != nullptr)
    {
        item = item->m_parentItem;
    }
    return item;
}

void FluHNavigationIconTextItem::expand()
{
    LOG_DEBUG << "called";
#ifdef _DEBUG
    // if (getText() == "Accessibility")
    //{
    //     QThread::msleep(0);
    //     if (m_items.size() > 0)
    //    {
    //        if (!m_items[0]->m_isDown)
    //        {
    //            QThread::msleep(0);
    //        }
    //    }
    //}
#endif

    m_isDown = !m_isDown;
    setArrowButtonToChevronUp();

    m_emptyWidget->setFixedWidth(30 * getDepth());
    if (m_items.size() > 0)
    {
        int h = 0;
        int maxW = 0;

        for (int i = 0; i < m_verticalLayout1->count(); i++)
        {
            auto item = (FluHNavigationIconTextItem*)(m_verticalLayout1->itemAt(i)->widget());
            item->getWrapWidget1()->setFixedHeight(36);
            if (item->m_isDown)
            {
                item->setFixedHeight(36);
            }

            h += item->height();
            item->m_emptyWidget->setFixedWidth(30 * item->getDepth());

            int tmpWidth = item->calcItemWidth();
            if (tmpWidth > maxW)
            {
                maxW = tmpWidth;
            }
        }

        // LOG_DEBUG << "item H:" << h << ", item W:" << maxW;

        for (int i = 0; i < m_verticalLayout1->count(); i++)
        {
            auto item = (FluHNavigationIconTextItem*)(m_verticalLayout1->itemAt(i)->widget());
            item->setFixedWidth(maxW);
        }

        m_wrapWidget2->setFixedHeight(h);
        m_wrapWidget1->setFixedWidth(maxW);
        m_wrapWidget2->setFixedWidth(maxW);
        setFixedWidth(maxW);
        setFixedHeight(m_wrapWidget1->height() + m_wrapWidget2->height());
        m_wrapWidget2->show();

        int callHierarchy = 0;
        adjustItemWidth(this, maxW, callHierarchy);
        adjustItemHeight(this);
    }

    LOG_DEBUG << "item:" << getText() << ", height:" << height();
}

void FluHNavigationIconTextItem::collapse()
{
#ifdef _DEBUG

#endif
    // LOG_DEBUG << "called";
    m_isDown = !m_isDown;

    setArrowButtonToChevronDown();

    // adjust height;
    setFixedHeight(36);
    if (m_items.size() > 0)
    {
        m_wrapWidget2->hide();
        adjustItemHeight(this);
    }

    // adjust width;
    int callHierarchy = 0;
    int maxW = calcItemWidth();
    adjustItemWidth(this, maxW, callHierarchy);
}

void FluHNavigationIconTextItem::clearAllItemsSelectState()
{
    auto rootItem = getRootItem();
    clearAllItemsSelectState(rootItem);
}

void FluHNavigationIconTextItem::clearAllItemsSelectState(FluHNavigationIconTextItem* item)
{
    if (item == nullptr)
        return;

    // LOG_DEBUG << "Item:" << item->getText() << "called";
    item->updateSelected(false);

    for (int i = 0; i < item->m_verticalLayout1->count() && !m_parentView; i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(item->m_verticalLayout1->itemAt(i)->widget());
        clearAllItemsSelectState(tmpItem);
    }
}

void FluHNavigationIconTextItem::updateAllItemsStyleSheet()
{
    auto rootItem = getRootItem();
    updateAllItemsStyleSheet(rootItem);
}

void FluHNavigationIconTextItem::updateAllItemsStyleSheet(FluHNavigationIconTextItem* item)
{
    if (item == nullptr)
        return;

    item->style()->polish(item);
    item->m_wrapWidget1->style()->polish(item->m_wrapWidget1);
    item->m_wrapWidget2->style()->polish(item->m_wrapWidget2);
    item->m_verticalIndicator->style()->polish(item->m_verticalIndicator);
    item->m_iconButton->style()->polish(item->m_iconButton);
    item->m_label->style()->polish(item->m_label);
    item->m_arrow->style()->polish(item->m_arrow);

    for (int i = 0; i < item->m_verticalLayout1->count() && !m_parentView; i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(item->m_verticalLayout1->itemAt(i)->widget());
        updateAllItemsStyleSheet(tmpItem);
        // updateSelected(true);
    }
}

void FluHNavigationIconTextItem::updateSelected(bool b)
{
    m_isSelected = b;
    setProperty("selected", b);
    m_wrapWidget1->setProperty("selected", b);
    m_wrapWidget2->setProperty("selected", b);

    if (parentIsNavigationView())
    {
        if (m_horizontalIndicator->width() > 0)
            m_horizontalIndicator->setFixedWidth(width() * 0.6);
        m_horizontalIndicator->animateSelect(b);
        m_verticalIndicator->setProperty("selected", false);
    }
    else
    {
        auto rootItem = getRootItem();
        if (rootItem != nullptr && rootItem->parentIsFlyIconTextItem())
        {
            m_horizontalIndicator->animateSelect(false);
            m_verticalIndicator->setProperty("selected", b);
        }
    }

    m_label->setProperty("selected", b);
}

void FluHNavigationIconTextItem::mouseReleaseEvent(QMouseEvent* event)
{
    QPoint pos = event->pos();
    if (!m_wrapWidget1->rect().contains(pos))
        return;

    emit itemClicked();
}

void FluHNavigationIconTextItem::onItemClicked()
{
    // LOG_DEBUG << getText() << " called";
    auto rootItem = getRootItem();
    if (rootItem == nullptr)
    {
        LOG_DEBUG << "root item empty.";
        return;
    }

#ifdef _DEBUG
    if (getText() == "Accessibility")
    {
        QThread::msleep(0);
    }

    if (getText() == "Screen reader support")
    {
        QThread::msleep(0);
    }
#endif

    auto navView = rootItem->getParentView();
    if (rootItem->parentIsFlyIconTextItem() && m_isDown)
    {
        expand();
    }
    else if (rootItem->parentIsFlyIconTextItem() && !m_isDown)
    {
        collapse();
    }
    else if (navView != nullptr && rootItem == this)
    {
        if (!getItems().empty())
        {
#ifdef _DEBUG
            // static int clickedCount = 0;
            // clickedCount++;
            // if (clickedCount == 2)
            // {
            // QThread::sleep(0);
            // }
#endif
            if (m_isDown)
            {
                m_isDown = !m_isDown;
                // LOG_DEBUG << getText() << " called";

                // LOG_DEBUG << "item:" << getText() << ", isDown:" << m_isDown;
                auto flyIconTextItem = new FluHNavigationFlyIconTextItem;
                flyIconTextItem->setNavView(navView);

                connect(flyIconTextItem, &FluHNavigationFlyIconTextItem::itemSelected, this, [=](QString key) {
                    if (!key.isEmpty() && navView)
                        emit navView->keyChanged(key);
                });

                connect(flyIconTextItem, &FluHNavigationFlyIconTextItem::itemClose, this, [=]() {
                    // LOG_DEBUG << "clicked Item:" << getText() << ", close it.";
                    bool isOnItem = geometry().contains(parentWidget()->mapFromGlobal(QCursor::pos()));
                    // LOG_DEBUG << getText() << "Item Close, "
                    //           << "isOnItem:" << isOnItem << ", isDown:"<<m_isDown;

                    if (!m_isDown && !isOnItem)
                    {
                        m_isDown = !m_isDown;
                        rootItem->setArrowButtonToChevronDown();
                        navView->setLastSelectedItem(nullptr);
                    }
                });

                navView->setLastSelectedItem(rootItem);
                navView->setFlyIconTextItem(flyIconTextItem);

                setArrowButtonToChevronUp();

                flyIconTextItem->setIconTextItems(getItems(), width());
                flyIconTextItem->setPositionRelativeTo(this, height());
            }
            else
            {
                // LOG_DEBUG << "681";
                bool isOnItem = geometry().contains(parentWidget()->mapFromGlobal(QCursor::pos()));
                if (isOnItem)
                {
                    m_isDown = !m_isDown;
                    rootItem->setArrowButtonToChevronDown();
                    navView->setLastSelectedItem(nullptr);
                }
            }
        }
    }

    // update select state;
    if (rootItem->parentIsFlyIconTextItem())
    {
        auto flyIconTextItem = rootItem->getParentFlyIconTextItem();
        flyIconTextItem->clearAllItemsSelectState();
        updateSelected(true);
        flyIconTextItem->updateAllItemsStyleSheet();

        if (isLeaf())
        {
            auto curNavView = flyIconTextItem->getNavView();
            curNavView->clearAllItemsSelectState();

            // update
            auto iconTextItem = (FluHNavigationIconTextItem*)curNavView->getLastSelectedItem();
            if (iconTextItem != nullptr)
            {
                iconTextItem->updateSelected(true);
                iconTextItem->setArrowButtonToChevronDown();
                iconTextItem->m_isDown = !iconTextItem->m_isDown;
            }
            curNavView->updateAllItemsStyleSheet();
            flyIconTextItem->close();
        }
        else
        {
            auto curNavView = flyIconTextItem->getNavView();
            curNavView->clearAllItemsSelectState();
            curNavView->updateAllItemsStyleSheet();
        }
    }
    else if (navView != nullptr)
    {
        navView->clearAllItemsSelectState();
        updateSelected(true);
        navView->updateAllItemsStyleSheet();
    }
}

void FluHNavigationIconTextItem::updateIconTheme()
{
    FluTheme theme = FluThemeUtils::getUtils()->getTheme();
    m_iconButton->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, theme));
    if (!m_items.empty())
    {
        if (FluThemeUtils::isLightTheme())
            m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, theme));
        else
            m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, theme));
    }
    else
    {
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::None, theme));
    }
}

void FluHNavigationIconTextItem::onThemeChanged()
{
    updateIconTheme();
    FluStyleSheetUtils::setQssByFileName("FluHNavigationIconTextItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
