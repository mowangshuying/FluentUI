#include "FluNavigationIconTextItem.h"
#include "FluNavigationMenuItem.h"
#include <QStyle>
#include "../FluUtils/FluUtils.h"
#include "FluNavigationView.h"

FluNavigationIconTextItem::FluNavigationIconTextItem(QWidget *parent /*= nullptr*/) : FluNavigationItem(parent)
{
    setFixedSize(320, 40);
    m_wrapWidget1 = new QWidget(this);
    m_wrapWidget2 = new QWidget(this);

    m_wrapWidget1->setObjectName("wrapWidget1");
    m_wrapWidget2->setObjectName("wrapWidget2");

    m_bSelected = false;
    m_wrapWidget1->setProperty("selected", false);
    setProperty("selected", false);

    m_emptyWidget = new QWidget(this);
    m_emptyWidget->setFixedSize(0, 0);
    // m_emptyWidget->hide();

    m_vMainLayout = new QVBoxLayout(this);
    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    m_vMainLayout->setSpacing(5);
    m_vMainLayout->addWidget(m_wrapWidget1);
    m_vMainLayout->addWidget(m_wrapWidget2);
    m_wrapWidget2->hide();

    m_hLayout1 = new QHBoxLayout(m_wrapWidget1);
    m_wrapWidget1->setFixedSize(320, 40);
    m_vMainLayout->addLayout(m_vMainLayout);

    m_vLayout1 = new QVBoxLayout(m_wrapWidget2);
    m_hLayout1->setContentsMargins(0, 4, 0, 4);
    m_indicator = new QWidget(this);
    m_icon = new QPushButton(this);
    m_label = new QLabel("Home");
    m_arrow = new QPushButton(this);

    m_hLayout1->addSpacing(4);
    m_hLayout1->addWidget(m_emptyWidget);
    m_hLayout1->addWidget(m_indicator);
    m_hLayout1->addWidget(m_icon);
    m_hLayout1->addSpacing(12);
    m_hLayout1->addWidget(m_label, 1);
    m_hLayout1->addWidget(m_arrow);

    m_hLayout1->setSpacing(0);

    m_indicator->setFixedHeight(18);
    m_indicator->setFixedWidth(4);
    m_icon->setFixedSize(30, 30);
    m_label->setWordWrap(true);

    m_vLayout1->setContentsMargins(0, 0, 0, 0);
    m_vLayout1->setSpacing(5);
    m_indicator->setObjectName("indicator");
    m_icon->setObjectName("icon");
    m_label->setObjectName("label");
    m_arrow->setObjectName("arrow");

    m_icon->setIconSize(QSize(25, 25));
    m_icon->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Home));

    m_arrow->setIconSize(QSize(25, 25));
    m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));
    m_bDown = true;
    m_bLong = true;
    m_arrow->hide();

    QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluNavigationIconTextItem.qss");
    setStyleSheet(qss);

    // m_currentWidth  = 320;
    m_parentItem = nullptr;
    m_parentView = nullptr;
    connect(m_arrow, &QPushButton::clicked, [=](bool b) { emit itemClicked(); });

    connect(m_icon, &QPushButton::clicked, [=](bool b) { emit itemClicked(); });
    connect(this, &FluNavigationIconTextItem::itemClicked, [=]() { onItemClicked(); });
}

FluNavigationIconTextItem::FluNavigationIconTextItem(QIcon icon, QString text, QWidget *parent /*= nullptr*/) : FluNavigationIconTextItem(parent)
{
    m_icon->setIcon(icon);
    m_label->setText(text);
}

FluNavigationIconTextItem::FluNavigationIconTextItem(QString text, QWidget *parent /*= nullptr*/) : FluNavigationIconTextItem(parent)
{
    m_icon->hide();
    // m_icon->setIcon(QIcon());
    m_label->setText(text);
}

QList<FluNavigationIconTextItem *> FluNavigationIconTextItem::getChildItems()
{
    return m_items;
}

void FluNavigationIconTextItem::setParentView(FluNavigationView *view)
{
    m_parentView = view;
}

FluNavigationView *FluNavigationIconTextItem::getParentView()
{
    return m_parentView;
}

void FluNavigationIconTextItem::addItem(FluNavigationIconTextItem *item)
{
    // item->m_currentWidth = m_currentWidth - 36;
    item->m_parentItem = this;
    m_items.append(item);

    int nDepth = item->getDepth();
    item->m_emptyWidget->setFixedWidth(36 * nDepth);
    item->show();

    m_vLayout1->addWidget(item);
    // m_vLayout1->addSpacing(15);
    m_arrow->show();
}

int FluNavigationIconTextItem::calcItemW2Height(FluNavigationIconTextItem *item)
{
    int nH = 0;
    for (int i = 0; i < item->m_vLayout1->count(); i++)
    {
        auto tmpItem = (FluNavigationIconTextItem *)item->m_vLayout1->itemAt(i)->widget();
        nH += tmpItem->height() + 5;
    }
    nH = nH + 5;
    return nH;
}

void FluNavigationIconTextItem::adjustItemHeight(FluNavigationIconTextItem *item)
{
    if (item == nullptr)
        return;

    int nH = calcItemW2Height(item);
    item->m_wrapWidget2->setFixedHeight(nH);
    item->setFixedHeight(item->m_wrapWidget1->height() + item->m_wrapWidget2->height());
    adjustItemHeight(item->m_parentItem);
}

int FluNavigationIconTextItem::getDepth()
{
    int nDepth = 0;
    FluNavigationIconTextItem *item = m_parentItem;
    while (item != nullptr)
    {
        nDepth++;
        item = item->m_parentItem;
    }
    return nDepth;
}

FluNavigationIconTextItem *FluNavigationIconTextItem::getRootItem()
{
    int nDepth = 0;
    FluNavigationIconTextItem *item = this;
    while (item->m_parentItem != nullptr)
    {
        // nDepth++;
        item = item->m_parentItem;
    }
    return item;
}

void FluNavigationIconTextItem::clearItemsSelectState(FluNavigationIconTextItem *item)
{
    if (item == nullptr)
        return;

    item->m_bSelected = false;
    item->setProperty("selected", false);
    item->m_wrapWidget1->setProperty("selected", false);
    item->m_indicator->setProperty("selected", false);
    for (int i = 0; i < item->m_vLayout1->count(); i++)
    {
        auto tmpItem = (FluNavigationIconTextItem *)item->m_vLayout1->itemAt(i)->widget();
        clearItemsSelectState(tmpItem);
    }
}

void FluNavigationIconTextItem::updateItemsStyleSheet(FluNavigationIconTextItem *item)
{
    if (item == nullptr)
        return;

    item->style()->polish(item);
    item->m_wrapWidget1->style()->polish(item->m_wrapWidget1);
    item->m_wrapWidget2->style()->polish(item->m_wrapWidget2);
    item->m_indicator->style()->polish(item->m_indicator);
    item->m_icon->style()->polish(item->m_icon);
    item->m_label->style()->polish(item->m_label);
    item->m_arrow->style()->polish(item->m_arrow);

    for (int i = 0; i < item->m_vLayout1->count(); i++)
    {
        auto tmpItem = (FluNavigationIconTextItem *)item->m_vLayout1->itemAt(i)->widget();
        updateItemsStyleSheet(tmpItem);
    }
}

void FluNavigationIconTextItem::updateSelected(bool b)
{
    m_bSelected = b;
    setProperty("selected", b);
    m_wrapWidget1->setProperty("selected", b);
    m_indicator->setProperty("selected", b);
    m_label->setProperty("selected", b);
}

void FluNavigationIconTextItem::enableThisItem(bool b)
{
    m_bEnableThisItem = b;
    setProperty("enableThisItem", b);
    m_wrapWidget1->setProperty("enableThisItem", b);
    m_indicator->setProperty("enableThisItem", b);
    m_label->setProperty("enableThisItem", b);
}

void FluNavigationIconTextItem::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    if (!m_wrapWidget1->rect().contains(pos))
        return;

    emit itemClicked();
}

void FluNavigationIconTextItem::onItemClicked()
{
    // enableThisItem equal false just return it.
    if (!m_bEnableThisItem)
        return;

    // get root item
    auto rootItem = getRootItem();
    if (rootItem == nullptr)
        return;

    auto navView = rootItem->getParentView();
    if (navView == nullptr)
        return;


    if (m_bDown && navView->isLong())
    {
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronUp));
        // display chid
        if (m_items.size() > 0)
        {
            int nH = 0;
            for (int i = 0; i < m_vLayout1->count(); i++)
            {
                auto item = (FluNavigationIconTextItem *)m_vLayout1->itemAt(i)->widget();
                nH += item->height() + 5;
            }

            m_wrapWidget2->setFixedHeight(nH);
            m_wrapWidget2->show();
            // set all item height;
            setFixedHeight(m_wrapWidget1->height() + m_wrapWidget2->height() + 5);
        }

        adjustItemHeight(m_parentItem);
        m_wrapWidget2->show();
    }
    
    if (!m_bDown && navView->isLong())
    {
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));
        setFixedHeight(40);
        if (m_items.size() > 0)
        {
            m_wrapWidget2->hide();
            adjustItemHeight(m_parentItem);
        }
    }

    m_bDown = !m_bDown;
    navView->clearAllItemsSelectState();  // clear state
    updateSelected(true);
    navView->updateAllItemsStyleSheet();  // update state
}
