#include "FluVNavigationFlyIconTextItem.h"
#include "FluVNavigationIconTextItem.h"
#include "../Utils/FluStyleSheetUtils.h"
#include "FluVNavigationView.h"

FluVNavigationFlyIconTextItem::FluVNavigationFlyIconTextItem(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_scrollView = new FluVScrollView;
    m_scrollView->setContentsMargins(0, 0, 0, 0);
    m_scrollView->setObjectName("centerWidget");

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    setLayout(m_mainLayout);

    m_scrollView->getMainLayout()->setContentsMargins(4, 4, 4, 4);
    m_scrollView->getMainLayout()->setSpacing(5);
    m_mainLayout->addWidget(m_scrollView);

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);
    // hide();
    onThemeChanged();
}

FluVNavigationFlyIconTextItem::~FluVNavigationFlyIconTextItem()
{
    // LOG_DEBUG << "called";
}

void FluVNavigationFlyIconTextItem::setItemWidth(int width)
{
}

void FluVNavigationFlyIconTextItem::setItemHeight(int height)
{
}

void FluVNavigationFlyIconTextItem::setIconTextItems(std::vector<FluVNavigationIconTextItem*> items)
{
    // copy items;

    FluVNavigationView* navView = nullptr;
    if (!items.empty())
    {
        // navView = items[0]->getRootItem()->getParentView();
        auto rootItem = items[0]->getRootItem();
        if (rootItem != nullptr)
            navView = rootItem->getParentView();
        // emit navView->keyChanged();
    }

    for (auto item : items)
    {
        auto newItem = new FluVNavigationIconTextItem(item);
        newItem->setParentFlyItem(this);
        m_scrollView->getMainLayout()->addWidget(newItem);
        m_items.push_back(newItem);
    }

    // get all items;
    std::vector<FluVNavigationIconTextItem*> allitems;
    for (auto item : m_items)
    {
        std::vector<FluVNavigationIconTextItem*> tmpitems;
        item->getAllItems(tmpitems);
        allitems.insert(allitems.end(), tmpitems.begin(), tmpitems.end());
        allitems.push_back(item);
    }

    // connect;
    for (auto item : allitems)
    {
        connect(item, &FluVNavigationIconTextItem::itemClicked, this, [=]() {
            if (navView != nullptr)
                emit navView->keyChanged(item->getKey());

            if (item->isLeaf())
            {
                close();
            }
        });
    }

    adjustItemWidth();
}

void FluVNavigationFlyIconTextItem::adjustItemHeight()
{
    int h = 0;
    for (auto item : m_items)
    {
        h += item->height();
    }
    h += m_scrollView->getMainLayout()->spacing() * (m_items.size() - 1) + m_scrollView->getMainLayout()->contentsMargins().top() + m_scrollView->getMainLayout()->contentsMargins().bottom();
    if (h > 450)
        h = 450;

    m_scrollView->setFixedHeight(h);
    h += m_mainLayout->contentsMargins().top() + m_mainLayout->contentsMargins().bottom();
    setFixedHeight(h);
}

void FluVNavigationFlyIconTextItem::adjustItemWidth()
{
    for (auto item : m_items)
    {
        item->adjustItemWidth(item);
    }

    int maxWidth = 0;
    for (auto item : m_items)
    {
        int width = item->calcItemWidth();
        if (width > maxWidth)
        {
            maxWidth = width;
        }
    }

    for (auto item : m_items)
    {
        item->getWrapWidget1()->setFixedWidth(maxWidth);
        item->setFixedWidth(maxWidth);
    }

    int totalMargins = m_scrollView->contentsMargins().left() + m_scrollView->contentsMargins().right() + m_scrollView->getMainLayout()->contentsMargins().left() + m_scrollView->getMainLayout()->contentsMargins().left();
    m_scrollView->setFixedWidth(maxWidth + totalMargins);
    setFixedWidth(maxWidth + totalMargins);
}

void FluVNavigationFlyIconTextItem::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluVNavigationFlyIconTextItem::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluVNavigationFlyIconTextItem.qss", m_scrollView, FluThemeUtils::getUtils()->getTheme());
    FluStyleSheetUtils::setQssByFileName("FluVNavigationFlyIconTextItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
