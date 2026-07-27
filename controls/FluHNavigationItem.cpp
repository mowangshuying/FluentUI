#include "FluHNavigationItem.h"

FluHNavigationItem::FluHNavigationItem(QWidget* parent /*= nullptr*/)
{
}

void FluHNavigationItem::setParentView(FluHNavigationView* view)
{
    m_parentView = view;
}

FluHNavigationView* FluHNavigationItem::getParentView()
{
    return m_parentView;
}

FluHNavigationItemType FluHNavigationItem::getItemType()
{
    return m_itemType;
}

void FluHNavigationItem::setItemType(FluHNavigationItemType itemType)
{
    m_itemType = itemType;
}
