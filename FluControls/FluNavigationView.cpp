#include "FluNavigationView.h"
#include "FluNavigationIconTextItem.h"
#include "FluNavigationMenuItem.h"
#include "../FluUtils/FluUtils.h"
#include "FluNavigationSettingsItem.h"

FluNavigationView::FluNavigationView(QWidget *parent /*= nullptr*/) : QWidget(parent)
{
    m_vLayout = new QVBoxLayout(this);
    m_vLayout->setContentsMargins(4, 8, 4, 8);
    m_widget1 = new QWidget(this);
    m_widget2 = new FluVScrollView(this);
    m_widget3 = new QWidget(this);

    m_vLayout1 = new QVBoxLayout(m_widget1);
    // m_vLayout2 = new QVBoxLayout(m_widget2);
    m_vLayout3 = new QVBoxLayout(m_widget3);

    m_vLayout1->setContentsMargins(0, 0, 0, 0);
    // m_vLayout2->setContentsMargins(0, 0, 0, 0);
    m_widget2->getMainLayout()->setContentsMargins(0, 0, 0, 0);
    m_vLayout3->setContentsMargins(0, 0, 0, 0);

    m_vLayout1->setSpacing(5);
    // m_vLayout2->setSpacing(5);
    m_vLayout3->setSpacing(5);

    m_vLayout1->setAlignment(Qt::AlignTop);
    //  m_vLayout2->setAlignment(Qt::AlignTop);
    m_widget2->getMainLayout()->setAlignment(Qt::AlignTop);
    m_vLayout3->setAlignment(Qt::AlignTop);

    //  auto srollArea = new QScrollArea(this);
    //  srollArea->setWidgetResizable(true);
    //  srollArea->setWidget(m_widget2);

    //   srollArea->setObjectName("srollArea");
    //   srollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_vLayout->addWidget(m_widget1);
    m_vLayout->addWidget(m_widget2, 1);
    m_vLayout->addWidget(m_widget3);

    m_widget1->setObjectName("widget1");
    m_widget2->setObjectName("widget2");
    m_widget3->setObjectName("widget3");

    auto menuButtonItem = new FluNavigationMenuItem(this);
    m_vLayout1->addWidget(menuButtonItem);

    QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluNavigationView.qss");
    setStyleSheet(qss);

    m_bLong = true;
    setFixedWidth(320 + 20);
    connect(menuButtonItem, &FluNavigationMenuItem::menuItemClicked, [=]() { onMenuItemClicked(); });
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
}

void FluNavigationView::addItemToLayout1(QWidget *item)
{
    m_vLayout1->addWidget(item, Qt::AlignTop);
}

void FluNavigationView::addItemToLayout2(QWidget *item)
{
    m_widget2->getMainLayout()->addWidget(item, Qt::AlignTop);

    auto iconTextItem = (FluNavigationIconTextItem *)item;
    iconTextItem->setParentView(this);
}

void FluNavigationView::addItemToLayout3(QWidget *item)
{
    m_vLayout3->addWidget(item);
    auto tmpItem = (FluNavigationItem *)item;
    tmpItem->setParentView(this);
}

void FluNavigationView::clearAllItemsSelectState()
{
    for (int i = 0; i < m_widget2->getMainLayout()->count(); i++)
    {
        auto curItem = (FluNavigationIconTextItem *)m_widget2->getMainLayout()->itemAt(i)->widget();
        curItem->clearAllItemsSelectState();
    }

    for (int i = 0; i < m_vLayout3->count(); i++)
    {
        auto curItem = (FluNavigationItem *)m_vLayout3->itemAt(i)->widget();
        curItem->clearAllItemsSelectState();
    }
}

void FluNavigationView::updateAllItemsStyleSheet()
{
    for (int i = 0; i < m_widget2->getMainLayout()->count(); i++)
    {
        auto curItem = (FluNavigationIconTextItem *)m_widget2->getMainLayout()->itemAt(i)->widget();
        curItem->updateAllItemsStyleSheet();
        curItem->update();
    }

    for (int i = 0; i < m_vLayout3->count(); i++)
    {
        auto curItem = (FluNavigationItem *)m_vLayout3->itemAt(i)->widget();
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
    for (int i = 0; i < m_widget1->layout()->count(); i++)
    {
        itemVct.push_back(m_widget1->layout()->itemAt(i)->widget());
    }

    for (int i = 0; i < m_widget2->getMainLayout()->count(); i++)
    {
        itemVct.push_back(m_widget2->getMainLayout()->itemAt(i)->widget());
    }

    for (int i = 0; i < m_widget3->layout()->count(); i++)
    {
        itemVct.push_back(m_widget3->layout()->itemAt(i)->widget());
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
        }

        setFixedWidth(48);
        m_bLong = false;
        m_widget2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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

            // auto iconTextItem = (FluNavigationIconTextItem *)(m_widget2->getMainLayout()->itemAt(i)->widget());
            // if (iconTextItem != nullptr)
            // {
            //     iconTextItem->setFixedWidth(320);
            //     iconTextItem->getWrapWidget1()->setFixedWidth(320);
            //     iconTextItem->showLabelArrow();
            // }

            // auto settingsItem = (FluNavigationSettingsItem *)(m_widget2->getMainLayout()->itemAt(i)->widget());
            // if (settingsItem != nullptr)
            // {
            //     settingsItem->setFixedWidth(320);
            //     settingsItem->showLabel();
            // }

            // auto item = (FluNavigationItem *)(m_widget2->getMainLayout()->itemAt(i)->widget());
            //  if (item != nullptr)
            //  {
            //      item->setLong(true);
            //  }
        }

        m_widget2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        setFixedWidth(320 + 20);
        m_bLong = true;
    }
}
