#include "FluHNavigationIconTextItem.h"
#include "FluHNavigationFlyIconTextItem.h"
#include <QThread>

FluHNavigationIconTextItem::FluHNavigationIconTextItem(QWidget* parent /*= nullptr*/) : FluHNavigationItem(parent)
{
    m_itemType = FluHNavigationItemType::IconText;
    m_parentView = nullptr;
    m_awesomeType = FluAwesomeType::None;
    m_parentItem = nullptr;

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

    m_vLayout1 = new QVBoxLayout;
    m_wrapWidget2->setLayout(m_vLayout1);

    m_iconBtn = new QPushButton;
    m_label = new QLabel;
    m_arrow = new QPushButton;

    m_hLayout1->addWidget(m_iconBtn);
    m_hLayout1->addWidget(m_label, 1);
    m_hLayout1->addWidget(m_arrow);

    m_vLayout1->setContentsMargins(0, 0, 0, 0);
    m_vLayout1->setSpacing(5);
    m_iconBtn->setObjectName("icon");
    m_label->setObjectName("label");
    m_arrow->setObjectName("arrow");

    m_iconBtn->setIconSize(QSize(24, 24));
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Home));
    m_iconBtn->setFixedWidth(30);

    m_arrow->setIconSize(QSize(18, 18));
    m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));
    m_arrow->setFixedWidth(25);

    connect(m_arrow, &QPushButton::clicked, this, [=](){ emit itemClicked();
        });
    connect(m_iconBtn, &QPushButton::clicked, this, [=]() { emit itemClicked(); });
    connect(this, &FluHNavigationIconTextItem::itemClicked, this, [=]() { onItemClicked();
    });

    setFixedHeight(40);
}

FluHNavigationIconTextItem::FluHNavigationIconTextItem(FluAwesomeType awesomeType, QString text, QWidget* parent /*= nullptr*/) : FluHNavigationIconTextItem(parent)
{
    m_awesomeType = awesomeType;
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType));
    m_label->setText(text);
    m_bHideIcon = false;
    onThemeChanged();
}

FluHNavigationIconTextItem::FluHNavigationIconTextItem(FluHNavigationIconTextItem* item) : FluHNavigationIconTextItem()
{
    itemClone(item);
    onThemeChanged();
}

 FluHNavigationIconTextItem::FluHNavigationIconTextItem(QString text, QWidget* parent /*= nullptr*/) : FluHNavigationIconTextItem(parent)
{
     m_awesomeType = FluAwesomeType::None;
     m_iconBtn->hide();
     m_bHideIcon = true;

     m_label->setText(text);
     onThemeChanged();
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
    item->m_parentItem = this;
    m_items.push_back(item);

    //int nDepth = item->getDepth();

    m_vLayout1->addWidget(item);
    m_arrow->show();
}

int FluHNavigationIconTextItem::calcItemW1Width()
{
    QMargins margins = m_wrapWidget1->contentsMargins();
    //int nIndicatorWidth = m_indicator->width();

    int nIconWidth = m_iconBtn->width();
    if (m_bHideIcon)
        nIconWidth = 0;

    int nSpacing = 8;
    int nLabelWidth = m_label->fontMetrics().boundingRect(m_label->text()).width();
    int nArrowWidth = m_arrow->width();
    if (m_items.empty())
    {
        nArrowWidth = 0;
        m_arrow->hide();
    }
    else
    {
        m_arrow->show();
    }

    // LOG_DEBUG << "Text:" << m_label->text() << "==========================================";
    // LOG_DEBUG << "margins left:" << margins.left() << ",margins right:" << margins.right();
    // LOG_DEBUG << "nIndicatorWidth:" << nIndicatorWidth;
    // LOG_DEBUG << "nIconWidth:" << nIconWidth;
    // LOG_DEBUG << "nSpacing:" << nSpacing;
    // LOG_DEBUG << "nLabelWidth:" << nLabelWidth;
    // LOG_DEBUG << "nArrowWidth:" << nArrowWidth;
    // LOG_DEBUG << "W1 width:" << margins.left() + nIndicatorWidth + nIconWidth + nSpacing + nLabelWidth + nArrowWidth + margins.right();

    //return margins.left() + nIndicatorWidth + nIconWidth + nSpacing + nLabelWidth + nArrowWidth + margins.right() + 20;
    return margins.left() + nIconWidth + nSpacing + nLabelWidth + nArrowWidth + margins.right() + 20;
}

int FluHNavigationIconTextItem::calcItemW2Height(FluHNavigationIconTextItem* item)
{
    int nH = 0;
    for (int i = 0; i < item->m_vLayout1->count(); i++)
    {
        auto tmpItem = (FluHNavigationIconTextItem*)(item->m_vLayout1->itemAt(i)->widget());
        nH += tmpItem->height() + 5;
    }
    nH += 5;
    return nH;
}

void FluHNavigationIconTextItem::adjustItemHeight(FluHNavigationIconTextItem* item)
{
    if (item == nullptr)
        return;

    LOG_DEBUG << item->getText();

    int nH = calcItemW2Height(item);
    item->m_wrapWidget2->setFixedHeight(nH);
    item->setFixedHeight(item->m_wrapWidget1->height() + item->m_wrapWidget2->height());

   // if (item->m_parentItem->m_parentView == nullptr)
   // {
        adjustItemHeight(item->m_parentItem);
   // }
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

void FluHNavigationIconTextItem::mouseReleaseEvent(QMouseEvent* event)
{
    QPoint pos = event->pos();
    if (!m_wrapWidget1->rect().contains(pos))
        return;

    emit itemClicked();
}

void FluHNavigationIconTextItem::onItemClicked()
{
    LOG_DEBUG << getText() <<" called";
    auto rootItem = getRootItem();
    if (rootItem == nullptr)
    {
        LOG_DEBUG << "root item empty.";
        return;
    }

#ifdef _DEBUG
    if (getText() == "Accessibility")
    {
        QThread::msleep(0);
    }
#endif

    LOG_DEBUG << "root item not empty.";
    auto navView = rootItem->getParentView();

    if (rootItem->parentIsFlyIconTextItem())
    {
        if (m_items.size() > 0)
        {
            int nH = 0;
            for (int i = 0; i < m_vLayout1->count(); i++)
            {
                auto item = (FluHNavigationIconTextItem*)(m_vLayout1->itemAt(i)->widget());
                LOG_DEBUG << item->getText();
                nH += item->height() + 5;
            }

            m_wrapWidget2->setFixedHeight(nH);
            m_wrapWidget2->show();
            setFixedHeight(m_wrapWidget1->height() + m_wrapWidget2->height() + 5);
        }
    }

    if (navView != nullptr && rootItem == this)
    {
        LOG_DEBUG << "parent view not empty.";
        if (!getItems().empty())
        {
            auto flyIconTextItem = new FluHNavigationFlyIconTextItem;
            flyIconTextItem->setIconTextItems(getItems());
            flyIconTextItem->show();
            QPoint gPoint = mapToGlobal(QPoint(0, height()));
            flyIconTextItem->move(gPoint.x(), gPoint.y());
            return;
        }
    }
    
    if (navView == nullptr)
    {
        if (!getItems().empty())
        {
            // expand---

        }
        else
        {

        }
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
