#include "FluHNavigationView.h"
#include "FluHNavigationIconTextItem.h"
#include "FluHNavigationMoreItem.h"

FluHNavigationView::FluHNavigationView(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_lastSelectedItem = nullptr;
    m_FlyIconTextItem = nullptr;

    m_layout = new QHBoxLayout;
    setLayout(m_layout);
    m_layout->setContentsMargins(8, 2, 8, 2);
    m_leftWrapWidget = new QWidget(this);
    m_MidWrapWidget = new QWidget(this);
    m_rightWrapWidget = new QWidget(this);

    m_moreItem = new FluHNavigationMoreItem(m_MidWrapWidget);
    m_moreItem->setFixedSize(40, 40);
    m_moreItem->setParentView(this);

    m_leftWrapLayout = new QHBoxLayout;
    m_rightWrapLayout = new QHBoxLayout;

    m_leftWrapWidget->setLayout(m_leftWrapLayout);
    m_rightWrapWidget->setLayout(m_rightWrapLayout);

    m_leftWrapLayout->setContentsMargins(0, 0, 0, 0);
    m_rightWrapLayout->setContentsMargins(0, 0, 0, 0);

    m_leftWrapLayout->setSpacing(5);
    m_rightWrapLayout->setSpacing(5);

    m_leftWrapLayout->setAlignment(Qt::AlignLeft);
    m_rightWrapLayout->setAlignment(Qt::AlignRight);

    m_layout->addWidget(m_leftWrapWidget);
    m_layout->addWidget(m_MidWrapWidget, 1);
    m_layout->addWidget(m_rightWrapWidget);

    setFixedHeight(40);
    onThemeChanged();
}

void FluHNavigationView::addItemToLeftLayout(QWidget* item)
{
    m_leftWrapLayout->addWidget(item, 0, Qt::AlignLeft);
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
    m_rightWrapLayout->addWidget(item, 0, Qt::AlignRight);
    auto curItem = (FluHNavigationItem*)item;
    curItem->setParentView(this);
    curItem->setParent(m_rightWrapWidget);
}

// void FluHNavigationView::removeItemMidLayout(QWidget* item)
//{
//  m_midWrapLayout->removeWidget(item);
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

    for (int i = 0; i < m_rightWrapLayout->count(); i++)
    {
        auto curItem = (FluHNavigationItem*)(m_rightWrapLayout->itemAt(i)->widget());
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

    for (int i = 0; i < m_rightWrapLayout->count(); i++)
    {
        auto curItem = (FluHNavigationItem*)(m_rightWrapLayout->itemAt(i)->widget());
        curItem->updateAllItemsStyleSheet();
        curItem->update();
    }

    m_moreItem->updateAllItemsStyleSheet();
}

void FluHNavigationView::resizeEvent(QResizeEvent* event)
{
    // LOG_DEBUG << "called ----------";

    m_hideItems.clear();
    int midWidth = 0;
    for (int i = 0; i < m_items.size(); i++)
    {
        m_items[i]->show();
        if (midWidth + m_items[i]->sizeHint().width() + m_moreItem->sizeHint().width() > m_MidWrapWidget->width())
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
            m_items[i]->move(midWidth, 0);
            midWidth += m_items[i]->sizeHint().width();
            // LOG_DEBUG << "IconTextItem Move to x:" << midWidth;
        }
    }

    if (m_hideItems.empty())
    {
        m_moreItem->hide();
    }
    else
    {
        m_moreItem->setParent(m_MidWrapWidget);
        m_moreItem->move(midWidth, 0);
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
