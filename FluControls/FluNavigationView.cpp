#include "FluNavigationView.h"

FluNavigationItem::FluNavigationItem(QWidget *parent /*= nullptr*/) : QWidget(parent)
{
    setFixedSize(320, 40);
    m_wrapTopW = new QWidget(this);
    m_wrapBottomW = new QWidget(this);

    m_wrapTopW->setObjectName("wrapWidget1");
    m_wrapBottomW->setObjectName("wrapWidget2");

    m_bSelected = false;
    m_wrapTopW->setProperty("selected", false);
    setProperty("selected", false);

    m_emptyWidget = new QWidget(this);
    m_emptyWidget->setFixedSize(0, 0);
    // m_emptyWidget->hide();

    m_vMainLayout = new QVBoxLayout(this);
    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    m_vMainLayout->setSpacing(0);
    m_vMainLayout->addWidget(m_wrapTopW);
    m_vMainLayout->addWidget(m_wrapBottomW);
    m_wrapBottomW->hide();

    m_hTopLayout = new QHBoxLayout(m_wrapTopW);
    m_wrapTopW->setFixedSize(320, 40);
    m_vMainLayout->addLayout(m_vMainLayout);

    m_vBottomLayout = new QVBoxLayout(m_wrapBottomW);
    m_hTopLayout->setContentsMargins(0, 4, 0, 4);
    m_indicator = new QWidget(this);
    m_icon = new QPushButton(this);
    m_label = new QLabel("Home");
    m_arrow = new QPushButton(this);

    m_hTopLayout->addSpacing(4);
    m_hTopLayout->addWidget(m_emptyWidget);
    m_hTopLayout->addWidget(m_indicator);
    m_hTopLayout->addWidget(m_icon);
    m_hTopLayout->addSpacing(12);
    m_hTopLayout->addWidget(m_label, 1);
    m_hTopLayout->addWidget(m_arrow);

    m_hTopLayout->setSpacing(0);

    m_indicator->setFixedHeight(18);
    m_indicator->setFixedWidth(4);
    m_icon->setFixedSize(30, 30);
    m_label->setWordWrap(true);

    m_vBottomLayout->setContentsMargins(0, 0, 0, 0);
    m_vBottomLayout->setSpacing(0);
    m_indicator->setObjectName("indicator");
    m_icon->setObjectName("icon");
    m_label->setObjectName("label");
    m_arrow->setObjectName("arrow");

    m_icon->setIconSize(QSize(30, 30));
    m_icon->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Home));

    m_arrow->setIconSize(QSize(30, 30));
    m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));
    m_bDown = true;
    m_bLong = true;
    m_arrow->hide();

    QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluNavigationItem.qss");
    setStyleSheet(qss);

    // m_currentWidth  = 320;
    m_parentItem = nullptr;
    m_parentView = nullptr;
    connect(m_arrow, &QPushButton::clicked, [=](bool b) {
        if (m_bDown)
        {
            LOG_DEBUG << "click down.";

            // LOG_DEBUG << "before height:" << height();
            m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronUp));
            // 展示子项目
            if (m_items.size() > 0)
            {
                int nH = 0;
                for (int i = 0; i < m_vBottomLayout->count(); i++)
                {
                    auto item = (FluNavigationItem *)m_vBottomLayout->itemAt(i)->widget();
                    nH += item->height();
                }

                m_wrapBottomW->setFixedHeight(nH);
                m_wrapBottomW->show();
                // 遍历所有子项目设置其长度
                setFixedHeight(m_wrapTopW->height() + m_wrapBottomW->height());
            }

            adjustItemHeight(m_parentItem);
            m_wrapBottomW->show();
            // show();
            // adjustItemHeight();
            m_bDown = false;
            // LOG_DEBUG << "end height:" << height();
        }
        else
        {
            m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));
            setFixedHeight(40);
            m_wrapBottomW->hide();

            adjustItemHeight(m_parentItem);

            m_bDown = true;
        }
    });

    connect(m_icon, &QPushButton::clicked, [=](bool b) {
        //	if (m_bLong)
        //	{
        //		m_bLong = false;
        //		m_label->hide();
        //		m_arrow->hide();
        //		setFixedWidth(48);
        //	}
        //	else
        //	{
        //		m_bLong = true;
        //		m_label->show();
        //		m_arrow->show();
        //		setFixedWidth(320);
        //	}
    });
}

FluNavigationItem::FluNavigationItem(QIcon icon, QString text, QWidget *parent /*= nullptr*/) : FluNavigationItem(parent)
{
    m_icon->setIcon(icon);
    m_label->setText(text);
}

FluNavigationItem::FluNavigationItem(QString text, QWidget *parent /*= nullptr*/) : FluNavigationItem(parent)
{
    m_icon->hide();
    // m_icon->setIcon(QIcon());
    m_label->setText(text);
}

QList<FluNavigationItem *> FluNavigationItem::getChildItems()
{
    return m_items;
}

void FluNavigationItem::setParentView(FluNavigationView *view)
{
    m_parentView = view;
}

FluNavigationView *FluNavigationItem::getParentView()
{
    return m_parentView;
}

void FluNavigationItem::addChildItem(FluNavigationItem *item)
{
    // item->m_currentWidth = m_currentWidth - 36;
    item->m_parentItem = this;
    m_items.append(item);

    int nDepth = item->getDepth();
    item->m_emptyWidget->setFixedWidth(36 * nDepth);
    item->show();

    m_vBottomLayout->addWidget(item);
    m_arrow->show();
}

int FluNavigationItem::calcItemW2Height(FluNavigationItem *item)
{
    int nH = 0;
    for (int i = 0; i < item->m_vBottomLayout->count(); i++)
    {
        auto tmpItem = (FluNavigationItem *)item->m_vBottomLayout->itemAt(i)->widget();
        nH += tmpItem->height();
    }
    return nH;
}

void FluNavigationItem::adjustItemHeight(FluNavigationItem *item)
{
    if (item == nullptr)
        return;

    int nH = calcItemW2Height(item);
    item->m_wrapBottomW->setFixedHeight(nH);
    item->setFixedHeight(item->m_wrapTopW->height() + item->m_wrapBottomW->height());
    adjustItemHeight(item->m_parentItem);
}

int FluNavigationItem::getDepth()
{
    int nDepth = 0;
    FluNavigationItem *item = m_parentItem;
    while (item != nullptr)
    {
        nDepth++;
        item = item->m_parentItem;
    }
    return nDepth;
}

FluNavigationItem *FluNavigationItem::getRootItem()
{
    int nDepth = 0;
    FluNavigationItem *item = this;
    while (item->m_parentItem != nullptr)
    {
        // nDepth++;
        item = item->m_parentItem;
    }
    return item;
}

void FluNavigationItem::clearItemsSelectState(FluNavigationItem *item)
{
    if (item == nullptr)
        return;

    item->m_bSelected = false;
    item->setProperty("selected", false);
    item->m_wrapTopW->setProperty("selected", false);
    item->m_indicator->setProperty("selected", false);
    for (int i = 0; i < item->m_vBottomLayout->count(); i++)
    {
        auto tmpItem = (FluNavigationItem *)item->m_vBottomLayout->itemAt(i)->widget();
        clearItemsSelectState(tmpItem);
    }
}

void FluNavigationItem::updateItemsStyleSheet(FluNavigationItem *item)
{
    if (item == nullptr)
        return;

    item->style()->polish(item);
    item->m_wrapTopW->style()->polish(item->m_wrapTopW);
    item->m_wrapBottomW->style()->polish(item->m_wrapBottomW);
    item->m_indicator->style()->polish(item->m_indicator);
    item->m_icon->style()->polish(item->m_icon);
    item->m_label->style()->polish(item->m_label);
    item->m_arrow->style()->polish(item->m_arrow);

    for (int i = 0; i < item->m_vBottomLayout->count(); i++)
    {
        auto tmpItem = (FluNavigationItem *)item->m_vBottomLayout->itemAt(i)->widget();
        updateItemsStyleSheet(tmpItem);
    }
}

void FluNavigationItem::updateSelected(bool b)
{
    m_bSelected = b;
    setProperty("selected", b);
    m_wrapTopW->setProperty("selected", b);
    m_indicator->setProperty("selected", b);
}

void FluNavigationItem::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    if (!m_wrapTopW->rect().contains(pos))
        return;

    // 清除所有item对象的状态
    auto rootItem = getRootItem();
    if (rootItem == nullptr)
        return;

    auto navView = rootItem->getParentView();
    if (navView == nullptr)
        return;

    navView->clearAllItemsSelectState();

    // emit itemClicked();
    updateSelected(true);

    navView->updateAllItemsStyleSheet();
}
