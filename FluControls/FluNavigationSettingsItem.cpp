#include "FluNavigationSettingsItem.h"
#include "FluNavigationView.h"

void FluNavigationSettingsItem::onItemClicked()
{
    m_icon->setReserveAngle(16);

    auto navView = getParentView();
    if (navView == nullptr)
        return;
    navView->clearAllItemsSelectState();
    updateSelected(true);
    navView->updateAllItemsStyleSheet();

    // updateSelected(true);
    // updateItemsStyleSheet();
}
