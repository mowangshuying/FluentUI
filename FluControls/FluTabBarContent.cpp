#include "FluTabBarContent.h"

FluTabBarContent::FluTabBarContent(QWidget* parent /*= nullptr*/) : QScrollArea(parent)
{
    setWidgetResizable(true);
    verticalScrollBar()->setEnabled(false);
    horizontalScrollBar()->setEnabled(true);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_hMainWidget = new QWidget(this);
    setWidget(m_hMainWidget);

    m_hMainWidget->setObjectName("mainWidget");

    m_hMainLayout = new QHBoxLayout;
    m_hMainWidget->setLayout(m_hMainLayout);
    m_hMainLayout->setContentsMargins(0, 4, 0, 0);

    m_hMidLayout = new QHBoxLayout;
    m_hMidLayout->setSpacing(0);

    m_hMidLayout->setAlignment(Qt::AlignLeft);
    m_hMidLayout->setSizeConstraint(QHBoxLayout::SetMinAndMaxSize);
    m_hMainLayout->addLayout(m_hMidLayout);
    m_hMainLayout->addStretch();

    m_hMainWidget->setFixedHeight(40);
    setFixedHeight(40);
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTabBarContent.qss", this);
}

void FluTabBarContent::addBarItem(FluTabBarItem* item)
{
    insertTabBarItem(-1, item);
}

void FluTabBarContent::insertTabBarItem(int nPos, FluTabBarItem* item)
{
    if ((nPos < -1) && (nPos > (int)(m_tabBarItems.size())))
    {
        return;
    }

    if (nPos == -1)
    {
        nPos = m_tabBarItems.size();
    }

    // insert to widget
    m_hMidLayout->insertWidget(nPos, item);
    m_tabBarItems.insert(m_tabBarItems.begin() + nPos, item);

    connect(item, &FluTabBarItem::clicked, [=]() {
        for (auto itemIter = m_tabBarItems.begin(); itemIter != m_tabBarItems.end(); itemIter++)
        {
            (*itemIter)->setSelected(false);
            (*itemIter)->style()->polish((*itemIter));
        }

        item->setSelected(true);
        item->style()->polish(item);
    });
}

void FluTabBarContent::removeTabBarItem(FluTabBarItem* item)
{
    m_hMidLayout->removeWidget(item);
    auto itf = std::find(m_tabBarItems.begin(), m_tabBarItems.end(), item);
    if (itf != m_tabBarItems.end())
    {
        m_tabBarItems.erase(itf);
    }
    item->deleteLater();
}

int FluTabBarContent::getSelectedTabBarItemIndex()
{
    int pos = -1;
    for (int i = 0; i < m_tabBarItems.size(); i++)
    {
        if (m_tabBarItems[i]->getSelected())
        {
            pos = i;
            break;
        }
    }
    return pos;
}

FluTabBarItem* FluTabBarContent::getSelectedTabBarItem()
{
    int itemIndex = getSelectedTabBarItemIndex();
    if (itemIndex < 0 || itemIndex >= m_tabBarItems.size())
        return nullptr;

    return m_tabBarItems[itemIndex];
}

std::vector<FluTabBarItem*> FluTabBarContent::getTabBarItems()
{
    return m_tabBarItems;
}

int FluTabBarContent::getTabBarItemMaxWidth()
{
    return m_nTabBarItemMaxWidth;
}

void FluTabBarContent::setTabBarItemMaxWidth(int nW)
{
    m_nTabBarItemMaxWidth = nW;
}

int FluTabBarContent::getTabBarItemMinWidth()
{
    return m_nTabBarItemMinWidth;
}

void FluTabBarContent::setTabBarItemMinWidth(int nW)
{
    m_nTabBarItemMinWidth = nW;
}

void FluTabBarContent::wheelEvent(QWheelEvent* event)
{
    QPointF pos(0, 0);
    QPointF gPos(0, 0);
    QPoint pixelDelta(0, 0);
    QPoint angleDelta(event->angleDelta().y(), 0);
    QWheelEvent wheelEvent(pos, gPos, pixelDelta, angleDelta, event->buttons(), event->modifiers(), event->phase(), event->inverted());
    QScrollArea::wheelEvent(&wheelEvent);
}

void FluTabBarContent::resizeEvent(QResizeEvent* event)
{
    QScrollArea::resizeEvent(event);
}
