#include "FluVNavigationFlyIconTextItem.h"
#include "FluVNavigationIconTextItem.h"
#include "../FluUtils/FluStyleSheetUitls.h"

FluVNavigationFlyIconTextItem::FluVNavigationFlyIconTextItem(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_vScrollView = new FluVScrollView;
    m_vScrollView->setObjectName("centerWidget");
    m_vMainLayout = new QVBoxLayout;
    setLayout(m_vMainLayout);

    m_vMainLayout->addWidget(m_vScrollView);
    m_vMainLayout->setContentsMargins(5, 5, 5, 5);

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    onThemeChanged();
}

FluVNavigationFlyIconTextItem::~FluVNavigationFlyIconTextItem()
{
    // LOG_DEBUG << "called";
}

void FluVNavigationFlyIconTextItem::setIconTextItems(std::vector<FluVNavigationIconTextItem*> items)
{
    // copy items;
    for (auto item : items)
    {
        auto newItem = new FluVNavigationIconTextItem(item);
        m_vScrollView->getMainLayout()->addWidget(newItem);
        m_items.push_back(newItem);

        connect(newItem, &FluVNavigationIconTextItem::itemClicked, this, [=]() {
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

void FluVNavigationFlyIconTextItem::adjustItemSize()
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

void FluVNavigationFlyIconTextItem::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluVNavigationFlyIconTextItem::onThemeChanged()
{
    // LOG_DEBUG << "called";
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVNavigationFlyIconTextItem.qss", m_vScrollView);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVNavigationFlyIconTextItem.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluVNavigationFlyIconTextItem.qss", m_vScrollView);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluVNavigationFlyIconTextItem.qss", this);
    }
}
