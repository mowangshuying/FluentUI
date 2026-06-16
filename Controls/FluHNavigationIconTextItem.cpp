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
    m_bDown = true;
    m_bParentIsFlyIconTextItem = false;
    m_bParentIsNavigationView = false;

    m_bHideIcon = false;
    m_bSelected = false;
    m_parentFlyIconTextItem = nullptr;

    m_wrapWidget1 = new QWidget;
    m_wrapWidget2 = new QWidget;

    m_wrapWidget1->setObjectName("wrapWidget1");
    m_wrapWidget2->setObjectName("wrapWidget2");

    m_hIndicator = new QWidget;
    m_hIndicator->setFixedHeight(4);
    m_hIndicator->setFixedWidth(18);
    m_hIndicator->setObjectName("hIndicator");

    m_hIndicatorWrap = new QWidget;
    m_hIndicatorLayout = new QHBoxLayout;
    m_hIndicatorLayout->setContentsMargins(0, 0, 0, 0);
    m_hIndicatorWrap->setFixedHeight(4);
    m_hIndicatorLayout->setAlignment(Qt::AlignHCenter);
    m_hIndicatorWrap->setLayout(m_hIndicatorLayout);

    m_hIndicatorLayout->addWidget(m_hIndicator);

    m_emptyWidget = new QWidget;
    m_emptyWidget->setFixedSize(0, 0);

    m_vMainLayout = new QVBoxLayout;
    setLayout(m_vMainLayout);

    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    m_vMainLayout->setSpacing(0);
    m_vMainLayout->addWidget(m_wrapWidget1);
    m_vMainLayout->addWidget(m_wrapWidget2);
    m_vMainLayout->addWidget(m_hIndicatorWrap);

    m_wrapWidget2->hide();
    m_hIndicator->hide();

    m_hLayout1 = new QHBoxLayout;
    m_wrapWidget1->setLayout(m_hLayout1);
    m_hLayout1->setContentsMargins(4, 4, 4, 4);
    m_hLayout1->setSpacing(0);

    m_vLayout1 = new QVBoxLayout;
    m_wrapWidget2->setLayout(m_vLayout1);

    m_vIndicator = new QWidget;
    m_iconBtn = new QPushButton;
    m_label = new QLabel;
    m_arrow = new QPushButton;

    m_hLayout1->addWidget(m_emptyWidget);
    m_hLayout1->addWidget(m_vIndicator);
    m_hLayout1->addWidget(m_iconBtn);
    m_hLayout1->addSpacing(8);
    m_hLayout1->addWidget(m_label, 1);
    m_hLayout1->addWidget(m_arrow);

    m_vIndicator->setFixedHeight(18);
    m_vIndicator->setFixedWidth(4);

    m_vLayout1->setContentsMargins(0, 0, 0, 0);
    m_vLayout1->setSpacing(0);

    // set obj names;
    m_vIndicator->setObjectName("indicator");
    m_iconBtn->setObjectName("icon");
    m_label->setObjectName("label");
    m_arrow->setObjectName("arrow");

    m_iconBtn->setIconSize(QSize(24, 24));
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::None, FluThemeUtils::getUtils()->getTheme()));
    m_iconBtn->setFixedSize(30, 30);

    m_arrow->setIconSize(QSize(18, 18));
    m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::None, FluThemeUtils::getUtils()->getTheme()));
    m_arrow->setFixedWidth(25);

    connect(m_arrow, &QPushButton::clicked, this, [=]() { emit itemClicked(); });
    connect(m_iconBtn, &QPushButton::clicked, this, [=]() { emit itemClicked(); });
    connect(this, &FluHNavigationIconTextItem::itemClicked, this, [=]() { onItemClicked(); });

    // fix height 40;
    setFixedHeight(40);
}

FluHNavigationIconTextItem::FluHNavigationIconTextItem(FluAwesomeType awesomeType, QString text, QWidget* parent /*= nullptr*/) : FluHNavigationIconTextItem(parent)
{
    m_awesomeType = awesomeType;
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType));
    m_label->setText(text);
    m_bHideIcon = false;
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
    m_iconBtn->hide();
    m_bHideIcon = true;

    m_label->setText(text);
    onThemeChanged();
}

FluHNavigationIconTextItem::~FluHNavigationIconTextItem()
{
}

void FluHNavigationIconTextItem::itemClone(FluHNavigationIconTextItem* item)
{
    m_iconBtn->setIcon(item->getIconBtn()->icon());
    m_label->setText(item->getLabel()->text());
    m_awesomeType = item->getAwesomeType();

    m_bHideIcon = item->getHideIcon();
    if (m_bHideIcon)
        m_iconBtn->hide();

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

    m_vLayout1->addWidget(item);
    setArrowBtnToChevronDown();
}

int FluHNavigationIconTextItem::calcItemW1Width()
{
    QMargins margins = m_wrapWidget1->contentsMargins();
    int leftMargins = margins.left();
    int rightMargins = margins.right();

    int emptyWidgetWidth = m_emptyWidget->width();
    int nIndicatorWidth = m_vIndicator->width();

    int nIconWidth = m_iconBtn->width();
    if (m_bHideIcon)
    {
        nIconWidth = 0;
    }

    int nSpacing = 8;
    int nLabelWidth = m_label->fontMetrics().boundingRect(m_label->text()).width();
    int nArrowWidth = m_arrow->width();

    // LOG_DEBUG << "Text:" << m_label->text() << "==========================================";
    // LOG_DEBUG << "margins left:" << margins.left() << ",margins right:" << margins.right();
    // LOG_DEBUG << "emptyWidgetWidth:" << emptyWidgetWidth;
    // LOG_DEBUG << "nIndicatorWidth:" << nIndicatorWidth;
    // LOG_DEBUG << "nIconWidth:" << nIconWidth;
    // LOG_DEBUG << "nSpacing:" << nSpacing;
    // LOG_DEBUG << "nLabelWidth:" << nLabelWidth;
    // LOG_DEBUG << "nArrowWidth:" << nArrowWidth;
    // LOG_DEBUG << "W1 width:" << leftMargins + emptyWidgetWidth + nIndicatorWidth + nIconWidth + nSpacing + nLabelWidth + nSpacing + nArrowWidth + nSpacing + rightMargins + 20;

    int nW1Width = leftMargins + emptyWidgetWidth + nIndicatorWidth + nIconWidth + nSpacing + nLabelWidth + nArrowWidth + rightMargins + 20;
    // LOG_DEBUG << "item:" << getText() << "W1Width:" << nW1Width;
    return nW1Width;
}

int FluHNavigationIconTextItem::calcItemWidth()
{
    if (m_bDown || isLeaf())
    {
        return calcItemW1Width();
    }

    int nW1Width = calcItemW1Width();
    int nW2Width = 0;
    for (int i = 0; i < m_vLayout1->layout()->count(); i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(m_vLayout1->itemAt(i)->widget());
        int nTmpItemWidth = tmpItem->calcItemW1Width();
        if (nTmpItemWidth > nW2Width)
        {
            nW2Width = nTmpItemWidth;
        }
    }

    int nWidth = qMax(nW1Width, nW2Width);
    // LOG_DEBUG << "item:" << getText() << "Width:" << nWidth;
    return nWidth;
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

    int nH = 0;
    for (int i = 0; i < item->m_vLayout1->count(); i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(item->m_vLayout1->itemAt(i)->widget());
        nH += tmpItem->height();
    }

    // LOG_DEBUG << "item:" << item->getText() << " wrap widget2 height:" << nH;
    return nH;
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

    if (item->m_bDown)
    {
        item->getWrapWidget2()->hide();
    }
    else
    {
        item->getWrapWidget2()->show();
    }

    int nH = calcItemW2Height(item);
    item->m_wrapWidget2->setFixedHeight(nH);
    item->setFixedHeight(item->m_wrapWidget1->height() + item->m_wrapWidget2->height());

    adjustItemHeight(item->m_parentItem);
    if (item->parentIsFlyIconTextItem())
    {
        auto flyIconTextItem = item->getParentFlyIconTextItem();
        auto vLayout = flyIconTextItem->getVScrollView()->getMainLayout();

        int nH = 0;
        for (int i = 0; i < vLayout->count(); i++)
        {
            auto tmpItem = (FluHNavigationIconTextItem*)(vLayout->itemAt(i)->widget());
            nH += tmpItem->sizeHint().height();
        }

        // nH += 15;
        nH += 15;
        if (nH > 600)
            nH = 600;

        flyIconTextItem->setFixedHeight(nH);
        flyIconTextItem->show();
    }
}

void FluHNavigationIconTextItem::adjustItemWidth(FluHNavigationIconTextItem* item, int& nMaxWidth, int& nCallHierarchy)
{
    if (item == nullptr)
    {
        return;
    }

    // QString sHierarchy = "";
    // for (int i = 0; i < nCallHierarchy; i++)
    //{
    //     sHierarchy += "\t";
    // }

    // LOG_DEBUG << sHierarchy << "text:" << getText() << ", child item count:" << item->m_vLayout1->count();

    int nItemW = item->calcItemWidth();
    if (nItemW > nMaxWidth)
    {
        nMaxWidth = nItemW;
    }

    for (int i = 0; i < item->m_vLayout1->count() && !item->m_bDown; i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(item->m_vLayout1->itemAt(i)->widget());
        nItemW = tmpItem->calcItemWidth();
        if (nItemW > nMaxWidth)
        {
            nMaxWidth = nItemW;
        }
    }

    // LOG_DEBUG << nCallHierarchy << "max width:" << nMaxWidth << ","
    //           << "item width:" << nItemW;

    item->setItemFixedWidth(nMaxWidth);
    for (int i = 0; i < item->m_vLayout1->count(); i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(item->m_vLayout1->itemAt(i)->widget());
        tmpItem->setItemFixedWidth(nMaxWidth);
    }

    // int nCallHierarchy = 0;
    adjustItemWidth(item->m_parentItem, nMaxWidth, nCallHierarchy);

    if (item->parentIsFlyIconTextItem())
    {
        int nMaxItemWidth = 0;

        auto vLayout = item->getParentFlyIconTextItem()->getVScrollView()->getMainLayout();
        for (int i = 0; i < vLayout->count(); i++)
        {
            auto tmpItem = (FluHNavigationIconTextItem*)(vLayout->itemAt(i)->widget());
            int nTmpWidth = tmpItem->calcItemWidth();
            if (nTmpWidth > nMaxItemWidth)
            {
                nMaxItemWidth = nTmpWidth;
            }
        }

        if (nMaxItemWidth > nMaxWidth)
            nMaxWidth = nMaxItemWidth;

        for (int i = 0; i < vLayout->count(); i++)
        {
            auto tmpItem = (FluHNavigationIconTextItem*)(vLayout->itemAt(i)->widget());
            tmpItem->setItemFixedWidth(nMaxWidth);
        }

        item->getParentFlyIconTextItem()->setFixedWidth(nMaxWidth + 15);
    }
}

void FluHNavigationIconTextItem::setItemFixedWidth(int nMaxWidth)
{
    setFixedWidth(nMaxWidth);
    getWrapWidget1()->setFixedWidth(nMaxWidth);
    getWrapWidget2()->setFixedWidth(nMaxWidth);

    for (int i = 0; i < m_vLayout1->count(); i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(m_vLayout1->itemAt(i)->widget());
        tmpItem->setFixedWidth(nMaxWidth);
        tmpItem->getWrapWidget1()->setFixedWidth(nMaxWidth);
        tmpItem->getWrapWidget2()->setFixedWidth(nMaxWidth);
    }
}

void FluHNavigationIconTextItem::setArrowBtnToChevronUp()
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

void FluHNavigationIconTextItem::setArrowBtnToChevronDown()
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
    int nDepth = 0;
    FluHNavigationIconTextItem* item = m_parentItem;
    while (item != nullptr)
    {
        nDepth++;
        item = item->m_parentItem;
    }
    return nDepth;
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
    //        if (!m_items[0]->m_bDown)
    //        {
    //            QThread::msleep(0);
    //        }
    //    }
    //}
#endif

    m_bDown = !m_bDown;
    setArrowBtnToChevronUp();

    m_emptyWidget->setFixedWidth(30 * getDepth());
    if (m_items.size() > 0)
    {
        int nH = 0;
        int nMaxW = 0;

        for (int i = 0; i < m_vLayout1->count(); i++)
        {
            auto item = (FluHNavigationIconTextItem*)(m_vLayout1->itemAt(i)->widget());
            item->getWrapWidget1()->setFixedHeight(36);
            if (item->m_bDown)
            {
                item->setFixedHeight(36);
            }

            nH += item->height();
            item->m_emptyWidget->setFixedWidth(30 * item->getDepth());

            int nTmpWidth = item->calcItemWidth();
            if (nTmpWidth > nMaxW)
            {
                nMaxW = nTmpWidth;
            }
        }

        // LOG_DEBUG << "item H:" << nH << ", item W:" << nMaxW;

        for (int i = 0; i < m_vLayout1->count(); i++)
        {
            auto item = (FluHNavigationIconTextItem*)(m_vLayout1->itemAt(i)->widget());
            item->setFixedWidth(nMaxW);
        }

        m_wrapWidget2->setFixedHeight(nH);
        m_wrapWidget1->setFixedWidth(nMaxW);
        m_wrapWidget2->setFixedWidth(nMaxW);
        setFixedWidth(nMaxW);
        setFixedHeight(m_wrapWidget1->height() + m_wrapWidget2->height());
        m_wrapWidget2->show();

        int nCallHierarchy = 0;
        adjustItemWidth(this, nMaxW, nCallHierarchy);
        adjustItemHeight(this);
    }

    LOG_DEBUG << "item:" << getText() << ", height:" << height();
}

void FluHNavigationIconTextItem::collapse()
{
#ifdef _DEBUG

#endif
    // LOG_DEBUG << "called";
    m_bDown = !m_bDown;

    setArrowBtnToChevronDown();

    // adjust height;
    setFixedHeight(36);
    if (m_items.size() > 0)
    {
        m_wrapWidget2->hide();
        adjustItemHeight(this);
    }

    // adjust width;
    int nCallHierarchy = 0;
    int nMaxW = calcItemWidth();
    adjustItemWidth(this, nMaxW, nCallHierarchy);
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

    for (int i = 0; i < item->m_vLayout1->count() && !m_parentView; i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(item->m_vLayout1->itemAt(i)->widget());
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
    item->m_vIndicator->style()->polish(item->m_vIndicator);
    item->m_hIndicator->style()->polish(item->m_hIndicator);
    item->m_iconBtn->style()->polish(item->m_iconBtn);
    item->m_label->style()->polish(item->m_label);
    item->m_arrow->style()->polish(item->m_arrow);

    for (int i = 0; i < item->m_vLayout1->count() && !m_parentView; i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(item->m_vLayout1->itemAt(i)->widget());
        updateAllItemsStyleSheet(tmpItem);
        // updateSelected(true);
    }
}

void FluHNavigationIconTextItem::updateSelected(bool b)
{
    m_bSelected = b;
    setProperty("selected", b);
    m_wrapWidget1->setProperty("selected", b);
    m_wrapWidget2->setProperty("selected", b);

    if (parentIsNavigationView())
    {
        m_hIndicator->setProperty("selected", b);
        m_vIndicator->setProperty("selected", false);
        // LOG_DEBUG << "item(parent is NavView):" << getText() << ", selected:" << b;
    }
    else
    {
        auto rootItem = getRootItem();
        if (rootItem != nullptr && rootItem->parentIsFlyIconTextItem())
        {
            m_hIndicator->setProperty("selected", false);
            m_vIndicator->setProperty("selected", b);
            // LOG_DEBUG << "item(parent is Not NavView):" << getText() << ", selected:" << b;
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
    if (rootItem->parentIsFlyIconTextItem() && m_bDown)
    {
        expand();
    }
    else if (rootItem->parentIsFlyIconTextItem() && !m_bDown)
    {
        collapse();
    }
    else if (navView != nullptr && rootItem == this)
    {
        if (!getItems().empty())
        {
#ifdef _DEBUG
            // static int nClickedCount = 0;
            // nClickedCount++;
            // if (nClickedCount == 2)
            // {
            // QThread::sleep(0);
            // }
#endif
            if (m_bDown)
            {
                m_bDown = !m_bDown;
                // LOG_DEBUG << getText() << " called";

                // LOG_DEBUG << "item:" << getText() << ", bDown:" << m_bDown;
                auto flyIconTextItem = new FluHNavigationFlyIconTextItem;
                flyIconTextItem->setNavView(navView);

                connect(flyIconTextItem, &FluHNavigationFlyIconTextItem::itemClose, this, [=]() {
                    // LOG_DEBUG << "clicked Item:" << getText() << ", close it.";
                    bool bOnItem = geometry().contains(parentWidget()->mapFromGlobal(QCursor::pos()));
                    // LOG_DEBUG << getText() << "Item Close, "
                    //           << "bOnItem:" << bOnItem << ", bDown:"<<m_bDown;

                    if (!m_bDown && !bOnItem)
                    {
                        m_bDown = !m_bDown;
                        rootItem->setArrowBtnToChevronDown();
                        navView->setLastSelectedItem(nullptr);
                    }
                });

                navView->setLastSelectedItem(rootItem);
                navView->setFlyIconTextItem(flyIconTextItem);

                setArrowBtnToChevronUp();

                flyIconTextItem->setIconTextItems(getItems());
                flyIconTextItem->show();

                // pos
                QPoint gPoint = mapToGlobal(QPoint(0, height()));
                flyIconTextItem->move(gPoint.x(), gPoint.y());
            }
            else
            {
                // LOG_DEBUG << "681";
                bool bOnItem = geometry().contains(parentWidget()->mapFromGlobal(QCursor::pos()));
                if (bOnItem)
                {
                    m_bDown = !m_bDown;
                    rootItem->setArrowBtnToChevronDown();
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
                iconTextItem->setArrowBtnToChevronDown();
                iconTextItem->m_bDown = !iconTextItem->m_bDown;
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

void FluHNavigationIconTextItem::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Light));
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHNavigationIconTextItem.qss", this);
        setArrowBtnToChevronDown();
    }
    else
    {
        m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Dark));
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHNavigationIconTextItem.qss", this);
        setArrowBtnToChevronUp();
    }
    FluStyleSheetUitls::setQssByFileName("FluHNavigationIconTextItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
