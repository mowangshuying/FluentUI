#include "FluHNavigationFlyIconTextItem.h"
#include "FluHNavigationIconTextItem.h"

FluHNavigationFlyIconTextItem::FluHNavigationFlyIconTextItem(QWidget* parent /*= nullptr*/)
{
    m_vScrollView = new FluVScrollView;
    m_vScrollView->setObjectName("centerWidget");

    m_vMainLayout = new QVBoxLayout;
    m_vMainLayout->setContentsMargins(5, 5, 5, 5);
    setLayout(m_vMainLayout);

    m_vScrollView->setContentsMargins(5, 5, 5, 5);
    m_vScrollView->getMainLayout()->setSpacing(0);
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

        newItem->setParentIsFlyIconTextItem(true);
        newItem->setParentIsNavigationView(false);
        
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
        int nWidth = item->calcItemW1Width();
        if (nWidth > nMaxWidth)
        {
            nMaxWidth = nWidth;
        }
    }

    int nMaxHeight = 0;
    for (auto item : m_items)
    {
        item->getWrapWidget1()->setFixedWidth(nMaxWidth);
        item->getWrapWidget1()->setFixedHeight(36);
        item->setFixedWidth(nMaxWidth);
        item->setFixedHeight(36);
        nMaxHeight += 36;
    }

    setFixedWidth(nMaxWidth + 25);
    setFixedHeight(nMaxHeight + 30);
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
