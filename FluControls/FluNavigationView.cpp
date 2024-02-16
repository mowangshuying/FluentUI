#include "FluNavigationView.h"
#include "FluNavigationIconTextItem.h"
#include "FluNavigationMenuItem.h"
#include "../FluUtils/FluUtils.h"
#include "FluNavigationSettingsItem.h"
#include "FluNavigationSearchItem.h"

FluNavigationView::FluNavigationView(QWidget *parent /*= nullptr*/) : QWidget(parent)
{
    m_vLayout = new QVBoxLayout(this);
    m_vLayout->setContentsMargins(4, 8, 4, 8);
    m_topWrapWidget = new QWidget(this);
    m_midVScrollView = new FluVScrollView(this);
    m_bottomWrapWidget = new QWidget(this);

    m_vTopWrapLayout = new QVBoxLayout(m_topWrapWidget);
    m_vBottomLayout = new QVBoxLayout(m_bottomWrapWidget);

    m_vTopWrapLayout->setContentsMargins(0, 0, 0, 0);
    m_midVScrollView->getMainLayout()->setContentsMargins(0, 0, 0, 0);
    m_vBottomLayout->setContentsMargins(0, 0, 0, 0);

    m_vTopWrapLayout->setSpacing(5);
    m_vBottomLayout->setSpacing(5);

    m_vTopWrapLayout->setAlignment(Qt::AlignTop);
    m_midVScrollView->getMainLayout()->setAlignment(Qt::AlignTop);
    m_vBottomLayout->setAlignment(Qt::AlignTop);

    m_vLayout->addWidget(m_topWrapWidget);
    m_vLayout->addWidget(m_midVScrollView, 1);
    m_vLayout->addWidget(m_bottomWrapWidget);

    m_topWrapWidget->setObjectName("widget1");
    m_midVScrollView->setObjectName("widget2");
    m_bottomWrapWidget->setObjectName("widget3");

    auto menuButtonItem = new FluNavigationMenuItem(this);
    m_vTopWrapLayout->addWidget(menuButtonItem);

    auto searchItem = new FluNavigationSearchItem;
    m_vTopWrapLayout->addWidget(searchItem);

    QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluNavigationView.qss");
    setStyleSheet(qss);

    m_bLong = true;
    setFixedWidth(320 + 20);
    connect(menuButtonItem, &FluNavigationMenuItem::menuItemClicked, [=]() { onMenuItemClicked(); });
    connect(searchItem, &FluNavigationSearchItem::itemClicked, [=]() { onMenuItemClicked(); });

    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
}

void FluNavigationView::addItemToTopLayout(QWidget *item)
{
    m_vTopWrapLayout->addWidget(item, Qt::AlignTop);
}

void FluNavigationView::addItemToMidLayout(QWidget *item)
{
    m_midVScrollView->getMainLayout()->addWidget(item, Qt::AlignTop);

    auto iconTextItem = (FluNavigationIconTextItem *)item;
    iconTextItem->setParentView(this);
}

void FluNavigationView::addItemToBottomLayout(QWidget *item)
{
    m_vBottomLayout->addWidget(item);
    auto tmpItem = (FluNavigationItem *)item;
    tmpItem->setParentView(this);
}

void FluNavigationView::clearAllItemsSelectState()
{
    for (int i = 0; i < m_midVScrollView->getMainLayout()->count(); i++)
    {
        auto curItem = (FluNavigationIconTextItem *)m_midVScrollView->getMainLayout()->itemAt(i)->widget();
        curItem->clearAllItemsSelectState();
    }

    for (int i = 0; i < m_vBottomLayout->count(); i++)
    {
        auto curItem = (FluNavigationItem *)m_vBottomLayout->itemAt(i)->widget();
        curItem->clearAllItemsSelectState();
    }
}

void FluNavigationView::updateAllItemsStyleSheet()
{
    for (int i = 0; i < m_midVScrollView->getMainLayout()->count(); i++)
    {
        auto curItem = (FluNavigationIconTextItem *)m_midVScrollView->getMainLayout()->itemAt(i)->widget();
        curItem->updateAllItemsStyleSheet();
        curItem->update();
    }

    for (int i = 0; i < m_vBottomLayout->count(); i++)
    {
        auto curItem = (FluNavigationItem *)m_vBottomLayout->itemAt(i)->widget();
        curItem->updateAllItemsStyleSheet();
    }
}

void FluNavigationView::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluNavigationView::onMenuItemClicked()
{
    QVector<QWidget *> itemVct;
    for (int i = 0; i < m_topWrapWidget->layout()->count(); i++)
    {
        itemVct.push_back(m_topWrapWidget->layout()->itemAt(i)->widget());
    }

    for (int i = 0; i < m_midVScrollView->getMainLayout()->count(); i++)
    {
        itemVct.push_back(m_midVScrollView->getMainLayout()->itemAt(i)->widget());
    }

    for (int i = 0; i < m_bottomWrapWidget->layout()->count(); i++)
    {
        itemVct.push_back(m_bottomWrapWidget->layout()->itemAt(i)->widget());
    }

    if (m_bLong)
    {
        // close all item in vLayout
        for (auto itemW : itemVct)
        {
            auto item = (FluNavigationItem *)(itemW);
            if (item != nullptr)
            {
                item->setLong(false);
                // item->setFixedWidth(40);
            }

            if (item->getItemType() == FluNavigationItemType::IconText)
            {
                auto iconTextItem = (FluNavigationIconTextItem *)(item);
                if (!iconTextItem->isDown())
                {
                    iconTextItem->onItemClicked();
                }
                iconTextItem->setFixedWidth(40);
                iconTextItem->getWrapWidget1()->setFixedWidth(40);
                iconTextItem->hideLabelArrow();
            }

            if (item->getItemType() == FluNavigationItemType::Setting)
            {
                auto settingsItem = (FluNavigationSettingsItem *)(item);
                if (settingsItem != nullptr)
                {
                    settingsItem->setFixedWidth(40);
                    settingsItem->hideLabel();
                }
            }

            if (item->getItemType() == FluNavigationItemType::Search)
            {
                auto searchItem = (FluNavigationSearchItem *)(item);
                if (searchItem != nullptr)
                {
                    searchItem->setFixedWidth(40);
                    searchItem->hideSearchEdit();
                }
            }

            if (item->getItemType() == FluNavigationItemType::Menu)
            {
                auto menuItem = (FluNavigationMenuItem *)(item);
                if (menuItem != nullptr)
                {
                    menuItem->setFixedWidth(40);
                }
            }
        }

        setFixedWidth(48);
        m_bLong = false;
        m_midVScrollView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
    else
    {
        for (auto itemW : itemVct)
        {
            auto item = (FluNavigationItem *)(itemW);
            if (item != nullptr)
            {
                item->setLong(true);
                // item->setFixedWidth(40);
            }

            if (item->getItemType() == FluNavigationItemType::IconText)
            {
                auto iconTextItem = (FluNavigationIconTextItem *)(item);
                iconTextItem->setFixedWidth(320);
                iconTextItem->getWrapWidget1()->setFixedWidth(320);
                iconTextItem->showLabelArrow();
            }

            if (item->getItemType() == FluNavigationItemType::Setting)
            {
                auto settingsItem = (FluNavigationSettingsItem *)(item);
                if (settingsItem != nullptr)
                {
                    settingsItem->setFixedWidth(320);
                    settingsItem->showLabel();
                }
            }

            if (item->getItemType() == FluNavigationItemType::Search)
            {
                auto searchItem = (FluNavigationSearchItem *)(item);
                if (searchItem != nullptr)
                {
                    searchItem->setFixedWidth(320);
                    searchItem->hideSearchButton();
                }
            }
        }

        m_midVScrollView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        setFixedWidth(320 + 20);
        m_bLong = true;
    }
}
