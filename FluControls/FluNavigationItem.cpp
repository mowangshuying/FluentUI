#include "FluNavigationItem.h"
#include "FluVNavigationView.h"

FluNavigationItem::FluNavigationItem(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
}

void FluNavigationItem::setParentView(FluVNavigationView* view)
{
    m_parentView = view;
}

FluVNavigationView* FluNavigationItem::getParentView()
{
    return m_parentView;
}

FluNavigationItemType FluNavigationItem::getItemType()
{
    return m_itemType;
}

void FluNavigationItem::setItemType(FluNavigationItemType itemType)
{
    m_itemType = itemType;
}

int FluNavigationItem::getItemHeight()  // to easy get item height
{
    return 0;
}
