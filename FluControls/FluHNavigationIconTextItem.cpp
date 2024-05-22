#include "FluHNavigationIconTextItem.h"

 FluHNavigationIconTextItem::FluHNavigationIconTextItem(QWidget* parent /*= nullptr*/) : FluHNavigationItem(parent)
{
    m_itemType = FluHNavigationItemType::IconText;
    m_parentView = nullptr;
    m_awesomeType = FluAwesomeType::None;

    m_wrapWidget1 = new QWidget;
    m_wrapWidget2 = new QWidget;

    m_wrapWidget1->setObjectName("wrapWidget1");
    m_wrapWidget2->setObjectName("wrapWidget2");

    m_vMainLayout = new QVBoxLayout;
    setLayout(m_vMainLayout);

    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    m_vMainLayout->setSpacing(5);
    m_vMainLayout->addWidget(m_wrapWidget1);
    m_vMainLayout->addWidget(m_wrapWidget2);
    m_wrapWidget2->hide();

    m_hLayout1 = new QHBoxLayout;
    setLayout(m_hLayout1);

    m_wrapWidget1->setLayout(m_hLayout1);
    m_hLayout1->setContentsMargins(4, 4, 4, 4);

    m_iconBtn = new QPushButton;
    m_label = new QLabel;
    m_arrow = new QPushButton;

    m_hLayout1->addWidget(m_iconBtn);
    m_hLayout1->addWidget(m_label, 1);
    m_hLayout1->addWidget(m_arrow);

    m_iconBtn->setObjectName("icon");
    m_label->setObjectName("label");
    m_arrow->setObjectName("arrow");

    m_iconBtn->setIconSize(QSize(24, 24));
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Home));

    m_arrow->setIconSize(QSize(18, 18));
    m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));
    m_arrow->setFixedWidth(25);

    setFixedHeight(40);
}

 FluHNavigationIconTextItem::FluHNavigationIconTextItem(FluAwesomeType awesomeType, QString text, QWidget* parent /*= nullptr*/) : FluHNavigationIconTextItem(parent)
{
    m_awesomeType = awesomeType;
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType));
    m_label->setText(text);
    onThemeChanged();
}

 FluHNavigationIconTextItem::FluHNavigationIconTextItem(FluHNavigationIconTextItem* item) : FluHNavigationIconTextItem()
{
     itemClone(item);
}

FluHNavigationIconTextItem::~FluHNavigationIconTextItem()
{
     
}

void FluHNavigationIconTextItem::itemClone(FluHNavigationIconTextItem* item)
{
    m_iconBtn->setIcon(item->getIconBtn()->icon());
    m_label->setText(item->getLabel()->text());
    m_awesomeType = item->getAwesomeType();

    m_bHideIcon = item->getHideIcon();
    if (m_bHideIcon)
        m_iconBtn->hide();

    std::vector<FluHNavigationIconTextItem*> items = item->getItems();
    for (auto tmpItem : items)
    {
        auto newItem = new FluHNavigationIconTextItem;
        newItem->itemClone(tmpItem);
        addItem(newItem);
    }
}

void FluHNavigationIconTextItem::getAllItems(std::vector<FluHNavigationIconTextItem*>& totalItems)
{
    std::vector<FluHNavigationIconTextItem*> items = getItems();
    for (auto item : items)
    {
        totalItems.push_back(item);
        item->getAllItems(totalItems);
    }
}

std::vector<FluHNavigationIconTextItem*> FluHNavigationIconTextItem::getAllItems()
{
    std::vector<FluHNavigationIconTextItem*> totalItems;
    getAllItems(totalItems);
    return totalItems;
}

void FluHNavigationIconTextItem::addItem(FluHNavigationIconTextItem* item)
{
    m_parentItem = this;
    m_items.push_back(item);
}

int FluHNavigationIconTextItem::getDepth()
{
    int nDepth = 0;
    FluHNavigationIconTextItem* item = m_parentItem;
    while (item != nullptr)
    {
        nDepth++;
        item = item->m_parentItem;
    }
    return nDepth;
}

FluHNavigationIconTextItem* FluHNavigationIconTextItem::getRootItem()
{
    FluHNavigationIconTextItem* item = this;
    while (item->m_parentItem != nullptr)
    {
        item = item->m_parentItem;
    }
    return item;
}

void FluHNavigationIconTextItem::onItemClicked()
{
    auto rootItem = getRootItem();
    if (rootItem == nullptr)
    {
        LOG_DEBUG << "root item empty.";
        return;
    }

    auto parentView = rootItem->getParentView();
    if (parentView == nullptr)
    {
        // show fly item;
        return;
    }

    if (parentView != nullptr)
    {

        return;
    }
}

void FluHNavigationIconTextItem::onThemeChanged()
{
    if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
    {
        m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, QColor(8, 8, 8)));
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, QColor(8, 8, 8)));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHNavigationIconTextItem.qss", this);
    }
    else
    {
        m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, QColor(239, 239, 239)));
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, QColor(239, 239, 239)));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHNavigationIconTextItem.qss", this);
    }
}
