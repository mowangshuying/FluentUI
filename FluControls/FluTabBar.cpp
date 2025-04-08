#include "FluTabBar.h"

FluTabBar::FluTabBar(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_hMainLayout = new QHBoxLayout;
    setLayout(m_hMainLayout);
    m_hMainLayout->setAlignment(Qt::AlignLeft);

    m_hMainLayout->setSpacing(0);
    m_hMainLayout->setContentsMargins(10, 0, 40, 0);
    m_hMainLayout->setSizeConstraint(QHBoxLayout::SetMinAndMaxSize);

    m_tabBarContent = new FluTabBarContent;
    m_tabBarContent->resize(0, height());
    m_hMainLayout->addWidget(m_tabBarContent);

    m_hMainLayout->addSpacing(8);

    m_addTabBtn = new QPushButton(this);
    m_addTabBtn->setFixedSize(30, 30);
    m_addTabBtn->setIconSize(QSize(20, 20));
    m_addTabBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Add));
    m_addTabBtn->setObjectName("addTabBtn");

    onThemeChanged();
    connect(m_addTabBtn, &QPushButton::clicked, [=]() { emit addTabBtnClicked(); });
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

std::vector<FluTabBarItem*> FluTabBar::getTabBarItems()
{
    return m_tabBarContent->getTabBarItems();
}

void FluTabBar::addBarItem(FluTabBarItem* item)
{
    m_tabBarContent->addBarItem(item);
    connect(item, &FluTabBarItem::sizeChanged, [=]() { adjustAddTabBtnPosition(); });
    connect(item, &FluTabBarItem::clickedCloseBtn, [this, item]() { removeTabBarItem(item); });
}

void FluTabBar::removeTabBarItem(FluTabBarItem* item)
{
    m_tabBarContent->removeTabBarItem(item);
}

void FluTabBar::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    adjustAddTabBtnPosition();
}

void FluTabBar::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    adjustAddTabBtnPosition();
}

void FluTabBar::adjustAddTabBtnPosition()
{
    std::vector<FluTabBarItem*> items = getTabBarItems();
    if (items.size() == 0)
    {
        int nX = 10;
        int nY = 5;
        m_addTabBtn->move(nX, nY);
        return;
    }
    else
    {
        auto tailItem = items[items.size() - 1];

        int nTmp = 0;
        for (int i = 0; i < items.size(); i++)
        {
            nTmp += items[i]->width();
        }

        int nX = nTmp + 20;
        int nY = 5;

        if (nX + 40 > width())
        {
            nX = width() - 40;
        }
        m_addTabBtn->move(nX, nY);
    }
}
