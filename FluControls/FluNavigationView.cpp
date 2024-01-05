#include "FluNavigationView.h"
#include "FluNavigationIconTextItem.h"
#include "FluNavigationMenuItem.h"

FluNavigationView::FluNavigationView(QWidget *parent /*= nullptr*/) : QWidget(parent)
{
    m_vLayout = new QVBoxLayout(this);
    m_vLayout->setContentsMargins(0, 0, 0, 0);
    m_widget1 = new QWidget(this);
    m_widget2 = new QWidget(this);
    m_widget3 = new QWidget(this);

    m_vLayout1 = new QVBoxLayout(m_widget1);
    m_vLayout2 = new QVBoxLayout(m_widget2);
    m_vLayout3 = new QVBoxLayout(m_widget3);

    m_vLayout1->setContentsMargins(0, 0, 0, 0);
    m_vLayout2->setContentsMargins(0, 0, 0, 0);
    m_vLayout3->setContentsMargins(0, 0, 0, 0);

    m_vLayout1->setSpacing(5);
    m_vLayout2->setSpacing(5);
    m_vLayout3->setSpacing(5);

    m_vLayout1->setAlignment(Qt::AlignTop);
    m_vLayout2->setAlignment(Qt::AlignTop);
    m_vLayout3->setAlignment(Qt::AlignTop);

    auto srollArea = new QScrollArea(this);
    srollArea->setWidgetResizable(true);
    srollArea->setWidget(m_widget2);

    srollArea->setObjectName("srollArea");
    srollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_vLayout->addWidget(m_widget1);
    m_vLayout->addWidget(srollArea, 1);
    m_vLayout->addWidget(m_widget3);

    m_widget1->setObjectName("widget1");
    m_widget2->setObjectName("widget2");
    m_widget3->setObjectName("widget3");

    auto menuButtonItem = new FluNavigationMenuItem(this);
    m_vLayout1->addWidget(menuButtonItem);

    QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluNavigationView.qss");
    setStyleSheet(qss);

    m_bLong = true;
    setFixedWidth(320 + 10);
    connect(menuButtonItem, &FluNavigationMenuItem::menuItemClicked, [=]() { onMenuItemClicked(); });
}

void FluNavigationView::addItemToLayout1(QWidget *item)
{
    m_vLayout1->addWidget(item, Qt::AlignTop);
}

void FluNavigationView::addItemToLayout2(QWidget *item)
{
    m_vLayout2->addWidget(item, Qt::AlignTop);

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
    for (int i = 0; i < m_vLayout2->count(); i++)
    {
        auto curItem = (FluNavigationIconTextItem *)m_vLayout2->itemAt(i)->widget();
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
    for (int i = 0; i < m_vLayout2->count(); i++)
    {
        auto curItem = (FluNavigationIconTextItem *)m_vLayout2->itemAt(i)->widget();
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
    if (m_bLong)
    {
        // close all item in vLayout
        for (int i = 0; i < m_vLayout2->count(); i++)
        {
            auto item = (FluNavigationIconTextItem *)(m_vLayout2->itemAt(i)->widget());
            if (item == nullptr)
                continue;

            if (!item->isDown())
            {
                item->onItemClicked();
            }
        }

        setFixedWidth(48);
        m_bLong = false;
    }
    else
    {
        setFixedWidth(320);
        m_bLong = true;
    }
}
