#include "FluVNavigationView.h"
#include "FluVNavigationIconTextItem.h"
#include "FluVNavigationMenuItem.h"
#include "../FluUtils/FluUtils.h"
#include "FluVNavigationSettingsItem.h"
#include "FluVNavigationSearchItem.h"
#include <QResizeEvent>

FluVNavigationView::FluVNavigationView(QWidget *parent /*= nullptr*/) : FluWidget(parent)
{
    m_nViewWidth = 320; // default width
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

    m_menuButtonItem = new FluVNavigationMenuItem(this);
    m_vTopWrapLayout->addWidget(m_menuButtonItem);

    m_searchItem = new FluVNavigationSearchItem;
    m_vTopWrapLayout->addWidget(m_searchItem);

    m_bLong = true;
    setFixedWidth(m_nViewWidth+ m_vLayout->contentsMargins().left() + m_vLayout->contentsMargins().right());

    // ani;
    m_animation = new QPropertyAnimation;
    m_animation->setDuration(100);
    m_animation->setPropertyName("value");

    m_valueObject = new FluValueObject;
    m_animation->setTargetObject(m_valueObject);
    m_animation->setStartValue(width());
    m_animation->setEndValue(40);

    connect(m_menuButtonItem, &FluVNavigationMenuItem::menuItemClicked, [=]() { onMenuItemClicked(); });
    connect(m_searchItem, &FluVNavigationSearchItem::itemClicked, [=]() { onMenuItemClicked(); });
    connect(m_searchItem, &FluVNavigationSearchItem::currentTextChanged, [=](QString text) {
        auto item = getItemByText(text);
        if (item != nullptr)
        {
            if (item->getItemType() == FluVNavigationItemType::IconText)
            {
                auto iconTextItem = (FluVNavigationIconTextItem *)(item);
                iconTextItem->onItemClickedDirect();
                emit searchKeyChanged(iconTextItem->getKey());
            }
            else if (item->getItemType() == FluVNavigationItemType::Setting)
            {
                auto settingsItem = (FluVNavigationSettingsItem *)item;
                settingsItem->onItemClicked();
                emit searchKeyChanged(settingsItem->getKey());
            }
        }
    });

    connect(m_animation, &QPropertyAnimation::valueChanged, this, [=]() {
        setFixedWidth(m_valueObject->getValue());
        update();
    });

    connect(m_animation, &QPropertyAnimation::finished, this, [=]() {
        if (!m_bLong)
            collapseView();
        // else
        //     expandView();
    });

    onThemeChanged();
}

void FluVNavigationView::addItemToTopLayout(QWidget *item)
{
    m_vTopWrapLayout->addWidget(item, 0, Qt::AlignTop);
}

void FluVNavigationView::addItemToMidLayout(QWidget *item)
{
    m_midVScrollView->getMainLayout()->addWidget(item, 0, Qt::AlignTop);

    auto iconTextItem = (FluVNavigationIconTextItem *)item;
    iconTextItem->setParentView(this);
}

void FluVNavigationView::addItemToBottomLayout(QWidget *item)
{
    m_vBottomLayout->addWidget(item);
    auto tmpItem = (FluVNavigationItem *)item;
    tmpItem->setParentView(this);
}

void FluVNavigationView::clearAllItemsSelectState()
{
    for (int i = 0; i < m_midVScrollView->getMainLayout()->count(); i++)
    {
        auto curItem = (FluVNavigationIconTextItem *)m_midVScrollView->getMainLayout()->itemAt(i)->widget();
        curItem->clearAllItemsSelectState();
    }

    for (int i = 0; i < m_vBottomLayout->count(); i++)
    {
        auto curItem = (FluVNavigationItem *)m_vBottomLayout->itemAt(i)->widget();
        curItem->clearAllItemsSelectState();
    }
}

void FluVNavigationView::updateAllItemsStyleSheet()
{
    for (int i = 0; i < m_midVScrollView->getMainLayout()->count(); i++)
    {
        auto curItem = (FluVNavigationIconTextItem *)m_midVScrollView->getMainLayout()->itemAt(i)->widget();
        curItem->updateAllItemsStyleSheet();
        curItem->update();
    }

    for (int i = 0; i < m_vBottomLayout->count(); i++)
    {
        auto curItem = (FluVNavigationItem *)m_vBottomLayout->itemAt(i)->widget();
        curItem->updateAllItemsStyleSheet();
    }
}

std::vector<FluVNavigationItem *> FluVNavigationView::getAllItems()
{
    std::vector<FluVNavigationItem *> items;
    for (int i = 0; i < m_topWrapWidget->layout()->count(); i++)
    {
        auto item = (FluVNavigationItem *)(m_topWrapWidget->layout()->itemAt(i)->widget());
        items.push_back(item);
    }

    for (int i = 0; i < m_midVScrollView->getMainLayout()->count(); i++)
    {
        auto item = (FluVNavigationItem *)(m_midVScrollView->getMainLayout()->itemAt(i)->widget());
        items.push_back(item);
    }

    for (int i = 0; i < m_bottomWrapWidget->layout()->count(); i++)
    {
        auto item = (FluVNavigationItem *)(m_bottomWrapWidget->layout()->itemAt(i)->widget());
        items.push_back(item);
    }

    std::vector<FluVNavigationItem *> allItems;
    allItems.insert(allItems.end(), items.begin(), items.end());
    for (auto item : items)
    {
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)item;
            std::vector<FluVNavigationIconTextItem *> totalItems = iconTextItem->getAllItems();
            allItems.insert(allItems.end(), totalItems.begin(), totalItems.end());
        }
    }
    return allItems;
}

std::vector<QString> FluVNavigationView::getAllItemsKeys()
{
    auto allItems = getAllItems();
    std::vector<QString> keys;
    for (auto item : allItems)
    {
        keys.push_back(item->getKey());
    }
    return keys;
}

FluVNavigationItem *FluVNavigationView::getItemByKey(QString key)
{
    std::vector<FluVNavigationItem *> items = getAllItems();
    FluVNavigationItem *item = nullptr;
    for (auto tmpItem : items)
    {
        if (tmpItem->getKey() == key)
        {
            item = tmpItem;
            break;
        }
    }

    return item;
}

std::vector<QString> FluVNavigationView::getAllItemsTexts()
{
    std::vector<QString> texts;
    auto allItems = getAllItems();
    for (auto item : allItems)
    {
        if (item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)item;
            texts.push_back(iconTextItem->getLabel()->text());
        }
        else if (item->getItemType() == FluVNavigationItemType::Setting)
        {
            auto settingsItem = (FluVNavigationSettingsItem *)item;
            texts.push_back(settingsItem->getLabel()->text());
        }
    }

    return texts;
}

FluVNavigationItem *FluVNavigationView::getItemByText(QString text)
{
    std::vector<FluVNavigationItem *> allItems = getAllItems();
    FluVNavigationItem *item = nullptr;
    for (auto item : allItems)
    {
        if (item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)item;
            // texts.push_back(iconTextItem->getLabel()->text());
            if (iconTextItem->getLabel()->text() == text)
                return item;
        }
        else if (item->getItemType() == FluVNavigationItemType::Setting)
        {
            auto settingsItem = (FluVNavigationSettingsItem *)item;
            if (settingsItem->getLabel()->text() == text)
                return item;
        }
    }

    return item;
}

void FluVNavigationView::updateSearchKeys()
{
    auto keys = getAllItemsTexts();
    m_searchItem->updateSearchKeys(keys);
}

inline void FluVNavigationView::expandView()
{
    // LOG_DEBUG << "called.";
    std::vector<QWidget *> itemVct;
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

    for (auto itemW : itemVct)
    {
        auto item = (FluVNavigationItem *)(itemW);
        if (item != nullptr)
        {
            item->setLong(true);
            // item->setFixedWidth(40);
        }

        if (item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->setFixedWidth(m_nViewWidth);
            iconTextItem->getWrapWidget1()->setFixedWidth(m_nViewWidth);
            iconTextItem->showLabelArrow();
        }

        if (item->getItemType() == FluVNavigationItemType::Setting)
        {
            auto settingsItem = (FluVNavigationSettingsItem *)(item);
            if (settingsItem != nullptr)
            {
                settingsItem->setFixedWidth(m_nViewWidth);
                settingsItem->showLabel();
            }
        }

        if (item->getItemType() == FluVNavigationItemType::Search)
        {
            auto searchItem = (FluVNavigationSearchItem *)(item);
            if (searchItem != nullptr)
            {
                searchItem->setFixedWidth(m_nViewWidth);
                searchItem->hideSearchButton();
            }
        }
    }
}

inline void FluVNavigationView::collapseView()
{
    // LOG_DEBUG << "called.";
    std::vector<QWidget *> itemVct;
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

    for (auto itemW : itemVct)
    {
        auto item = (FluVNavigationItem *)(itemW);
        if (item != nullptr)
        {
            item->setLong(false);
            // item->setFixedWidth(40);
        }

        if (item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            //  if (!iconTextItem->isDown())
            // {
            //     iconTextItem->onItemClicked();
            // }
            iconTextItem->setFixedWidth(40);
            iconTextItem->getWrapWidget1()->setFixedWidth(40);
            iconTextItem->hideLabelArrow();
        }

        if (item->getItemType() == FluVNavigationItemType::Setting)
        {
            auto settingsItem = (FluVNavigationSettingsItem *)(item);
            if (settingsItem != nullptr)
            {
                settingsItem->setFixedWidth(40);
                settingsItem->hideLabel();
            }
        }

        if (item->getItemType() == FluVNavigationItemType::Search)
        {
            auto searchItem = (FluVNavigationSearchItem *)(item);
            if (searchItem != nullptr)
            {
                searchItem->setFixedWidth(40);
                searchItem->hideSearchEdit();
            }
        }

        if (item->getItemType() == FluVNavigationItemType::Menu)
        {
            auto menuItem = (FluVNavigationMenuItem *)(item);
            if (menuItem != nullptr)
            {
                menuItem->setFixedWidth(40);
            }
        }
    }
}

void FluVNavigationView::collapseDownView()
{
    std::vector<QWidget *> itemVct;
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

    for (auto itemW : itemVct)
    {
        auto item = (FluVNavigationItem *)(itemW);
        if (item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            if (!iconTextItem->isDown())
            {
                iconTextItem->onItemClicked();
            }
        }
    }
}

void FluVNavigationView::resizeEvent(QResizeEvent *event)
{
    // LOG_DEBUG << event->size();
}

void FluVNavigationView::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluVNavigationView::onMenuItemClicked()
{
    // LOG_DEBUG << "called.";
    if (m_bLong)
    {
        collapseDownView();
        m_animation->setStartValue(width());
        m_animation->setEndValue(40 + m_vLayout->contentsMargins().left() + m_vLayout->contentsMargins().right());
        m_animation->start();
        m_bLong = false;
    }
    else
    {
        expandView();

        m_animation->setStartValue(width());
        m_animation->setEndValue(m_nViewWidth + m_vLayout->contentsMargins().left() + m_vLayout->contentsMargins().right());
        m_animation->start();
        m_bLong = true;
    }
}

void FluVNavigationView::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluVNavigationView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
