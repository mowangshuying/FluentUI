#include "FluVNavigationItem.h"
#include "FluVNavigationView.h"
#include "FluVNavigationFlyIconTextItem.h"
#include "FluVNavigationIconTextItem.h"

FluVNavigationItem::FluVNavigationItem(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_parentView = nullptr;
    m_flyItem = nullptr;
    m_state = FluVNavigationState::None;
    m_bLong = true;
}

void FluVNavigationItem::setState(FluVNavigationState state)
{
    m_state = state;
}

FluVNavigationState FluVNavigationItem::getState()
{
    return m_state;
}

void FluVNavigationItem::setParentView(FluVNavigationView* view)
{
    m_parentView = view;
}

FluVNavigationView* FluVNavigationItem::getParentView()
{
    return m_parentView;
}

FluVNavigationFlyIconTextItem* FluVNavigationItem::getFlyItem()
{
    if (m_itemType == FluVNavigationItemType::IconText)
    {
        auto item = (FluVNavigationIconTextItem*)this;
        while (item->getParentItem() != nullptr)
            item = item->getParentItem();
        return item->m_flyItem;
    }
    return nullptr;
    // return m_flyItem;
}

void FluVNavigationItem::setParentFlyItem(FluVNavigationFlyIconTextItem* flyItem)
{
    m_flyItem = flyItem;
}

FluVNavigationItemType FluVNavigationItem::getItemType()
{
    return m_itemType;
}

void FluVNavigationItem::setItemType(FluVNavigationItemType itemType)
{
    m_itemType = itemType;
}

int FluVNavigationItem::getItemHeight()  // to easy get item height
{
    return 0;
}

void FluVNavigationItem::setLong(bool bLong)
{
    setProperty("isLong", QVariant::fromValue(bLong));
    m_bLong = bLong;
    style()->polish(this);
}

bool FluVNavigationItem::isLong()
{
    return m_bLong;
}

QString FluVNavigationItem::getKey()
{
    return m_key;
}

void FluVNavigationItem::setKey(QString key)
{
    m_key = key;
}
