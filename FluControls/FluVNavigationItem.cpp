#include "FluVNavigationItem.h"
#include "FluVNavigationView.h"

FluVNavigationItem::FluVNavigationItem(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
}

void FluVNavigationItem::setParentView(FluVNavigationView* view)
{
    m_parentView = view;
}

FluVNavigationView* FluVNavigationItem::getParentView()
{
    return m_parentView;
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
