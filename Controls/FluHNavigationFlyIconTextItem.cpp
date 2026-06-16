#include "FluHNavigationFlyIconTextItem.h"
#include "FluHNavigationIconTextItem.h"

FluHNavigationFlyIconTextItem::FluHNavigationFlyIconTextItem(QWidget* parent /*= nullptr*/)
{
    m_vScrollView = new FluVScrollView;
    m_vScrollView->setObjectName("centerWidget");

    m_vMainLayout = new QVBoxLayout;
    m_vMainLayout->setContentsMargins(5, 5, 5, 5);
    m_vMainLayout->setSpacing(0);
    setLayout(m_vMainLayout);

    // m_vScrollView->setContentsMargins(0, 0, 0, 0);
    m_vScrollView->getMainLayout()->setContentsMargins(0, 0, 0, 0);
    m_vScrollView->getMainLayout()->setSpacing(0);
    m_vScrollView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_vMainLayout->addWidget(m_vScrollView);

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

        m_vScrollView->getMainLayout()->addWidget(newItem);
        m_items.push_back(newItem);
    }

    adjustItemWidth();
}

void FluHNavigationFlyIconTextItem::adjustItemWidth()
{
    int nMaxWidth = 0;
    for (auto item : m_items)
    {
        int nWidth = item->calcItemW1Width();
        if (nWidth > nMaxWidth)
        {
            nMaxWidth = nWidth;
        }
    }

    for (auto item : m_items)
    {
        item->getWrapWidget1()->setFixedWidth(nMaxWidth);
        item->getWrapWidget2()->setFixedWidth(nMaxWidth);
        item->setFixedWidth(nMaxWidth);
        item->setFixedHeight(36);
    }
    setFixedWidth(nMaxWidth + m_vScrollView->getMainLayout()->contentsMargins().left() + m_vScrollView->getMainLayout()->contentsMargins().right());
}

QVBoxLayout* FluHNavigationFlyIconTextItem::getMainLayout()
{
    return m_vMainLayout;
}

FluVScrollView* FluHNavigationFlyIconTextItem::getVScrollView()
{
    return m_vScrollView;
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
    m_bCloseByClickedItem = b;
}

bool FluHNavigationFlyIconTextItem::setCloseByClickedItem()
{
    return m_bCloseByClickedItem;
}

void FluHNavigationFlyIconTextItem::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluHNavigationFlyIconTextItem.qss", m_vScrollView, FluThemeUtils::getUtils()->getTheme());
    FluStyleSheetUitls::setQssByFileName("FluHNavigationFlyIconTextItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
