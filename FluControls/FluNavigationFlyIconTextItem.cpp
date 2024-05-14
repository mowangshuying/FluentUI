#include "FluNavigationFlyIconTextItem.h"
#include "FluNavigationIconTextItem.h"
#include "../FluUtils/FluStyleSheetUitls.h"

FluNavigationFlyIconTextItem::FluNavigationFlyIconTextItem(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_widget = new FluVScrollView;
    m_widget->setObjectName("centerWidget");
    m_vMainLayout = new QVBoxLayout;
    setLayout(m_vMainLayout);

    m_vMainLayout->addWidget(m_widget);
    m_vMainLayout->setContentsMargins(5, 5, 5, 5);

    // m_vCenterLayout = new QVBoxLayout;
    // m_vCenterLayout->setContentsMargins(5, 5, 5, 5);
    // m_widget->setLayout(m_vCenterLayout);

    m_widget->getMainLayout()->setContentsMargins(5, 5, 5, 5);
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNavigationFlyIconTextItem.qss", m_widget);
    // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNavigationFlyIconTextItem.qss", this);
    onThemeChanged();
}

 FluNavigationFlyIconTextItem::~FluNavigationFlyIconTextItem()
{
     //LOG_DEBUG << "called";
 }

void FluNavigationFlyIconTextItem::setIconTextItems(std::vector<FluNavigationIconTextItem*> items)
{
    // copy items;
    for (auto item : items)
    {
        auto newItem = new FluNavigationIconTextItem(item);
        m_widget->getMainLayout()->addWidget(newItem);
        m_items.push_back(newItem);

        connect(newItem, &FluNavigationIconTextItem::itemClicked, [=]() {
            // item->onItemClickedDirect();
            if (newItem->isLeaf())
            {
                emit item->itemClicked();
                close();
            }
        });
    }

    adjustItemSize();
}

void FluNavigationFlyIconTextItem::adjustItemSize()
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

    for (auto item : m_items)
    {
        item->getWrapWidget1()->setFixedWidth(nMaxWidth);
        item->setFixedWidth(nMaxWidth);
    }

    // m_widget->setFixedWidth(nMaxWidth + 10);
    setFixedWidth(nMaxWidth + 25);
}

void FluNavigationFlyIconTextItem::onThemeChanged()
{
    LOG_DEBUG << "called";
    if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNavigationFlyIconTextItem.qss", m_widget);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNavigationFlyIconTextItem.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluNavigationFlyIconTextItem.qss", m_widget);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluNavigationFlyIconTextItem.qss", this);
    }
}
