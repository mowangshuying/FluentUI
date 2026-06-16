#include "FluHNavigationView.h"
#include "FluHNavigationIconTextItem.h"
#include "FluHNavigationMoreItem.h"

FluHNavigationView::FluHNavigationView(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_lastSelectedItem = nullptr;
    m_FlyIconTextItem = nullptr;

    m_hLayout = new QHBoxLayout;
    setLayout(m_hLayout);
    m_hLayout->setContentsMargins(8, 2, 8, 2);
    m_leftWrapWidget = new QWidget(this);
    m_MidWrapWidget = new QWidget(this);
    m_rightWrapWidget = new QWidget(this);

    m_moreItem = new FluHNavigationMoreItem(m_MidWrapWidget);
    m_moreItem->setFixedSize(40, 40);
    m_moreItem->setParentView(this);

    m_hLeftWrapLayout = new QHBoxLayout;
    m_hRightWrapLayout = new QHBoxLayout;

    m_leftWrapWidget->setLayout(m_hLeftWrapLayout);
    m_rightWrapWidget->setLayout(m_hRightWrapLayout);

    m_hLeftWrapLayout->setContentsMargins(0, 0, 0, 0);
    m_hRightWrapLayout->setContentsMargins(0, 0, 0, 0);

    m_hLeftWrapLayout->setSpacing(5);
    m_hRightWrapLayout->setSpacing(5);

    m_hLeftWrapLayout->setAlignment(Qt::AlignLeft);
    m_hRightWrapLayout->setAlignment(Qt::AlignRight);

    m_hLayout->addWidget(m_leftWrapWidget);
    m_hLayout->addWidget(m_MidWrapWidget, 1);
    m_hLayout->addWidget(m_rightWrapWidget);

    setFixedHeight(48);
    onThemeChanged();
}

void FluHNavigationView::addItemToLeftLayout(QWidget* item)
{
    m_hLeftWrapLayout->addWidget(item, 0, Qt::AlignLeft);
}

void FluHNavigationView::addItemToMidLayout(QWidget* item)
{
    auto iconTextItem = (FluHNavigationIconTextItem*)item;
    iconTextItem->setParentView(this);
    item->setParent(m_MidWrapWidget);

    iconTextItem->setParentIsFlyIconTextItem(false);
    iconTextItem->setParentIsNavigationView(true);
    m_items.push_back(iconTextItem);
}

void FluHNavigationView::addItemToRightLayout(QWidget* item)
{
    m_hRightWrapLayout->addWidget(item, 0, Qt::AlignRight);
    auto curItem = (FluHNavigationItem*)item;
    curItem->setParentView(this);
    curItem->setParent(m_rightWrapWidget);
}

// void FluHNavigationView::removeItemMidLayout(QWidget* item)
//{
//  m_hMidWrapLayout->removeWidget(item);
//  auto itf = std::find(m_items.begin(), m_items.end)
//}

std::vector<FluHNavigationIconTextItem*> FluHNavigationView::getHideItems()
{
    return m_hideItems;
}

void FluHNavigationView::clearAllItemsSelectState()
{
    for (int i = 0; i < m_items.size(); i++)
    {
        auto curItem = m_items[i];
        curItem->clearAllItemsSelectState();
    }

    for (int i = 0; i < m_hRightWrapLayout->count(); i++)
    {
        auto curItem = (FluHNavigationItem*)(m_hRightWrapLayout->itemAt(i)->widget());
        curItem->clearAllItemsSelectState();
    }

    m_moreItem->clearAllItemsSelectState();
}

void FluHNavigationView::updateAllItemsStyleSheet()
{
    for (int i = 0; i < m_items.size(); i++)
    {
        auto curItem = m_items[i];
        curItem->updateAllItemsStyleSheet();
        curItem->update();
    }

    for (int i = 0; i < m_hRightWrapLayout->count(); i++)
    {
        auto curItem = (FluHNavigationItem*)(m_hRightWrapLayout->itemAt(i)->widget());
        curItem->updateAllItemsStyleSheet();
        curItem->update();
    }

    m_moreItem->updateAllItemsStyleSheet();
}

void FluHNavigationView::resizeEvent(QResizeEvent* event)
{
    // LOG_DEBUG << "called ----------";

    m_hideItems.clear();
    int nMidWidth = 0;
    for (int i = 0; i < m_items.size(); i++)
    {
        m_items[i]->show();
        if (nMidWidth + m_items[i]->sizeHint().width() + m_moreItem->sizeHint().width() > m_MidWrapWidget->width())
        {
            for (int j = i; j < m_items.size(); j++)
            {
                m_items[j]->hide();
                m_hideItems.push_back(m_items[j]);
            }
            break;
        }
        else
        {
            m_items[i]->move(nMidWidth, 0);
            nMidWidth += m_items[i]->sizeHint().width();
            // LOG_DEBUG << "IconTextItem Move to x:" << nMidWidth;
        }
    }

    if (m_hideItems.empty())
    {
        m_moreItem->hide();
    }
    else
    {
        m_moreItem->setParent(m_MidWrapWidget);
        m_moreItem->move(nMidWidth, 0);
        m_moreItem->show();
    }
}

void FluHNavigationView::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
