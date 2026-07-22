#include "FluTabBarContent.h"

FluTabBarContent::FluTabBarContent(QWidget* parent /*= nullptr*/) : QScrollArea(parent)
{
    setWidgetResizable(true);
    verticalScrollBar()->setEnabled(false);
    horizontalScrollBar()->setEnabled(true);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_mainWidget = new QWidget(this);
    setWidget(m_mainWidget);

    m_mainWidget->setObjectName("mainWidget");

    m_mainLayout = new QHBoxLayout;
    m_mainWidget->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 4, 0, 0);

    m_midLayout = new QHBoxLayout;
    m_midLayout->setSpacing(0);

    m_midLayout->setAlignment(Qt::AlignLeft);
    m_mainLayout->addLayout(m_midLayout);
    m_mainLayout->addStretch();

    m_mainWidget->setFixedHeight(40);
    setFixedHeight(40);
    FluStyleSheetUtils::setQssByFileName("FluTabBarContent.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluTabBarContent::addBarItem(FluTabBarItem* item)
{
    insertTabBarItem(-1, item);
}

void FluTabBarContent::insertTabBarItem(int pos, FluTabBarItem* item)
{
    if ((pos < -1) && (pos > (int)(m_tabBarItems.size())))
    {
        return;
    }

    if (pos == -1)
    {
        pos = m_tabBarItems.size();
    }

    // insert to widget
    m_midLayout->insertWidget(pos, item);
    m_tabBarItems.insert(m_tabBarItems.begin() + pos, item);

    item->setSelected(false);
    if (m_tabBarItems.size() == 1)
    {
        item->setSelected(true);
        }

        item->adjustWidgetSize();

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
    m_midLayout->removeWidget(item);
    auto itf = std::find(m_tabBarItems.begin(), m_tabBarItems.end(), item);
    if (itf != m_tabBarItems.end())
    {
        m_tabBarItems.erase(itf);
    }
    item->deleteLater();

    bool isHasSelected = false;
    for (auto itemIter = m_tabBarItems.begin(); itemIter != m_tabBarItems.end(); itemIter++)
    {
        if ((*itemIter)->getSelected())
        {
            isHasSelected = true;
            break;
        }
    }

    if (!isHasSelected && m_tabBarItems.size() > 0)
    {
        m_tabBarItems[0]->setSelected(true);
        m_tabBarItems[0]->style()->polish(m_tabBarItems[0]);
    }
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
    return m_tabBarItemMaxWidth;
}

void FluTabBarContent::setTabBarItemMaxWidth(int w)
{
    m_tabBarItemMaxWidth = w;
}

int FluTabBarContent::getTabBarItemMinWidth()
{
    return m_tabBarItemMinWidth;
}

void FluTabBarContent::setTabBarItemMinWidth(int w)
{
    m_tabBarItemMinWidth = w;
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
