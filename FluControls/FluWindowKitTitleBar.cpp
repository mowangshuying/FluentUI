#include "FluWindowKitTitleBar.h"
#include "../FluUtils/FluUtils.h"

FluWindowKitTitleBar::FluWindowKitTitleBar(QWidget* parent /*= nullptr*/) : QFrame(parent)
{
    m_w = nullptr;
    init();
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluWindowKitTitleBar.qss", this);
}

void FluWindowKitTitleBar::init()
{
    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setContentsMargins(QMargins());
    m_hMainLayout->setSpacing(0);

    for (int i = FluWKTitleBarItem::IconButton; i <= FluWKTitleBarItem::CloseButton; i++)
    {
        insertDefaultSpace(i);
    }

    setLayout(m_hMainLayout);
}
