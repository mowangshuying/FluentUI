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

        connect(newItem, &FluHNavigationIconTextItem::itemClicked, this, [=]() {
            if (newItem->isLeaf())
            {
                emit item->itemClicked();
                close();
            }
        });
    }

    adjustItemWidth();
}

void FluHNavigationFlyIconTextItem::adjustItemWidth()
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
        item->getWrapWidget2()->setFixedWidth(nMaxWidth);

        item->setFixedWidth(nMaxWidth);
        item->setFixedHeight(36);
        nMaxHeight += 36;
    }

    LOG_DEBUG << "vScrollView sizeHint:" << m_vScrollView->sizeHint();
    LOG_DEBUG << "HFlyIconItem sizeHint:" << sizeHint();

    setFixedWidth(nMaxWidth + 10);
    // setFixedHeight(nMaxHeight + 10);
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
