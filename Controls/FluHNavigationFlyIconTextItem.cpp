#include "FluHNavigationFlyIconTextItem.h"
#include "FluHNavigationIconTextItem.h"

FluHNavigationFlyIconTextItem::FluHNavigationFlyIconTextItem(QWidget* parent /*= nullptr*/)
{
    m_scrollView = new FluVScrollView;
    m_scrollView->setObjectName("centerWidget");

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setContentsMargins(5, 5, 5, 5);
    m_mainLayout->setSpacing(0);
    setLayout(m_mainLayout);

    // m_scrollView->setContentsMargins(0, 0, 0, 0);
    m_scrollView->getMainLayout()->setContentsMargins(0, 0, 0, 0);
    m_scrollView->getMainLayout()->setSpacing(0);
    m_scrollView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_mainLayout->addWidget(m_scrollView);

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    onThemeChanged();
}

void FluHNavigationFlyIconTextItem::setIconTextItems(std::vector<FluHNavigationIconTextItem*> items)
{
    for (auto item : items)
    {
        auto newItem = new FluHNavigationIconTextItem(item);
        newItem->setFixedHeight(36);
        newItem->getWrapWidget1()->setFixedHeight(36);
        newItem->getWrapWidget2()->hide();

        newItem->setParentIsFlyIconTextItem(true);
        newItem->setParentIsNavigationView(false);
        newItem->setParentFlyIconTextItem(this);

        m_scrollView->getMainLayout()->addWidget(newItem);
        m_items.push_back(newItem);
    }

    adjustItemWidth();
}

void FluHNavigationFlyIconTextItem::adjustItemWidth()
{
    int maxWidth = 0;
    for (auto item : m_items)
    {
        int width = item->calcItemW1Width();
        if (width > maxWidth)
        {
            maxWidth = width;
        }
    }

    for (auto item : m_items)
    {
        item->getWrapWidget1()->setFixedWidth(maxWidth);
        item->getWrapWidget2()->setFixedWidth(maxWidth);
        item->setFixedWidth(maxWidth);
        item->setFixedHeight(36);
    }
    setFixedWidth(maxWidth + m_scrollView->getMainLayout()->contentsMargins().left() + m_scrollView->getMainLayout()->contentsMargins().right());
}

QVBoxLayout* FluHNavigationFlyIconTextItem::getMainLayout()
{
    return m_mainLayout;
}

FluVScrollView* FluHNavigationFlyIconTextItem::getVScrollView()
{
    return m_scrollView;
}

void FluHNavigationFlyIconTextItem::clearAllItemsSelectState()
{
    for (int i = 0; i < m_items.size(); i++)
    {
        auto curItem = m_items[i];
        curItem->clearAllItemsSelectState();
    }
}

void FluHNavigationFlyIconTextItem::updateAllItemsStyleSheet()
{
    for (int i = 0; i < m_items.size(); i++)
    {
        auto curItem = m_items[i];
        curItem->updateAllItemsStyleSheet();
        curItem->update();
    }
}

void FluHNavigationFlyIconTextItem::setNavView(FluHNavigationView* view)
{
    m_NavView = view;
}

FluHNavigationView* FluHNavigationFlyIconTextItem::getNavView()
{
    return m_NavView;
}

void FluHNavigationFlyIconTextItem::getCloseByClickedItem(bool b)
{
    m_isCloseByClickedItem = b;
}

bool FluHNavigationFlyIconTextItem::setCloseByClickedItem()
{
    return m_isCloseByClickedItem;
}

void FluHNavigationFlyIconTextItem::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluHNavigationFlyIconTextItem.qss", m_scrollView, FluThemeUtils::getUtils()->getTheme());
    FluStyleSheetUtils::setQssByFileName("FluHNavigationFlyIconTextItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
