#include "FluHNavigationFlyIconTextItem.h"
#include "FluHNavigationIconTextItem.h"

FluHNavigationFlyIconTextItem::FluHNavigationFlyIconTextItem(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_scrollView = new FluVScrollView;
    m_scrollView->setObjectName("centerWidget");

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setContentsMargins(3, 3, 3, 3);
    m_mainLayout->setSpacing(0);
    setLayout(m_mainLayout);

    m_scrollView->getMainLayout()->setContentsMargins(0, 0, 0, 0);
    m_scrollView->getMainLayout()->setSpacing(0);
    m_scrollView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_mainLayout->addWidget(m_scrollView);

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    onThemeChanged();
}


void FluHNavigationFlyIconTextItem::setIconTextItems(std::vector<FluHNavigationIconTextItem*> items, int parentWidth)
{
    m_items.clear();
    for (auto item : items)
    {
        auto newItem = new FluHNavigationIconTextItem(item);
        newItem->setFixedHeight(34);
        newItem->getWrapWidget1()->setFixedHeight(34);
        newItem->getWrapWidget2()->hide();
        newItem->hideHorizontalIndicator();

        newItem->setParentIsFlyIconTextItem(true);
        newItem->setParentIsNavigationView(false);
        newItem->setParentFlyIconTextItem(this);

        connect(newItem, &FluHNavigationIconTextItem::itemClicked, this, [=]() {
            if (!newItem->getKey().isEmpty())
                emit itemSelected(newItem->getKey());
        });

        m_scrollView->getMainLayout()->addWidget(newItem);
        m_items.push_back(newItem);
    }

    adjustItemWidth(parentWidth);
}

void FluHNavigationFlyIconTextItem::adjustItemWidth(int minWidth)
{
    int maxWidth = minWidth;
    for (auto item : m_items)
    {
        int w = item->calcItemW1Width();
        if (w > maxWidth)
            maxWidth = w;
    }

    for (auto item : m_items)
    {
        item->getWrapWidget1()->setFixedWidth(maxWidth);
        item->getWrapWidget2()->setFixedWidth(maxWidth);
        item->setFixedWidth(maxWidth);
        item->setFixedHeight(34);
    }

    int totalWMargins = m_scrollView->getMainLayout()->contentsMargins().left() + m_scrollView->getMainLayout()->contentsMargins().right()
                     + m_mainLayout->contentsMargins().left() + m_mainLayout->contentsMargins().right();
    setFixedWidth(maxWidth + totalWMargins);

    //int contentHeight = m_items.size() * 34;
    int contentHeight = 0;
    for (auto item : m_items)
    {
        contentHeight += item->height();
    }

    int maxH = qMin(contentHeight, 400);
    m_scrollView->setFixedHeight(maxH);

    int totalHMargins = m_scrollView->getMainLayout()->contentsMargins().top() + m_scrollView->getMainLayout()->contentsMargins().bottom()
        + m_mainLayout->contentsMargins().top() + m_mainLayout->contentsMargins().bottom();
    setFixedHeight(maxH + totalHMargins);
}

QVBoxLayout* FluHNavigationFlyIconTextItem::getMainLayout()
{
    return m_mainLayout;
}

FluVScrollView* FluHNavigationFlyIconTextItem::getVScrollView()
{
    return m_scrollView;
}

void FluHNavigationFlyIconTextItem::clearAllItemsSelectState()
{
    for (int i = 0; i < m_items.size(); i++)
    {
        auto curItem = m_items[i];
        curItem->clearAllItemsSelectState();
    }
}

void FluHNavigationFlyIconTextItem::updateAllItemsStyleSheet()
{
    for (int i = 0; i < m_items.size(); i++)
    {
        auto curItem = m_items[i];
        curItem->updateAllItemsStyleSheet();
        curItem->update();
    }
}

void FluHNavigationFlyIconTextItem::setNavView(FluHNavigationView* view)
{
    m_NavView = view;
}

FluHNavigationView* FluHNavigationFlyIconTextItem::getNavView()
{
    return m_NavView;
}

void FluHNavigationFlyIconTextItem::getCloseByClickedItem(bool b)
{
    m_isCloseByClickedItem = b;
}

bool FluHNavigationFlyIconTextItem::setCloseByClickedItem()
{
    return m_isCloseByClickedItem;
}

void FluHNavigationFlyIconTextItem::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluHNavigationFlyIconTextItem.qss", m_scrollView, FluThemeUtils::getUtils()->getTheme());
    FluStyleSheetUtils::setQssByFileName("FluHNavigationFlyIconTextItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
