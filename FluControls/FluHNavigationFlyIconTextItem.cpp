#include "FluHNavigationFlyIconTextItem.h"
#include "FluHNavigationIconTextItem.h"

FluHNavigationFlyIconTextItem::FluHNavigationFlyIconTextItem(QWidget* parent /*= nullptr*/)
{
    m_vScrollView = new FluVScrollView;
    m_vScrollView->setObjectName("centerWidget");

    m_vMainLayout = new QVBoxLayout;
    setLayout(m_vMainLayout);

    m_vScrollView->setContentsMargins(5, 5, 5, 5);
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
        m_vScrollView->getMainLayout()->addWidget(newItem);
        m_items.push_back(newItem);

        connect(newItem, &FluHNavigationIconTextItem::itemClicked, this, [=]() { 
            if (newItem->isLeaf())
            {
                emit item->itemClicked();
                close();
            }
        });
    }

    adjustItemSize();
}

void FluHNavigationFlyIconTextItem::adjustItemSize()
{
    LOG_DEBUG << "called";
    int nMaxWidth = 0;
    for (auto item : m_items)
    {
        //
    }
}

void FluHNavigationFlyIconTextItem::onThemeChanged()
{
    if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHNavigationFlyIconTextItem.qss", m_vScrollView);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHNavigationFlyIconTextItem.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHNavigationFlyIconTextItem.qss", m_vScrollView);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHNavigationFlyIconTextItem.qss", this);
    }
}
