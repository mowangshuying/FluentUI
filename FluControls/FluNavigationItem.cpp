#include "FluNavigationItem.h"

FluNavigationItem::FluNavigationItem(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
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
