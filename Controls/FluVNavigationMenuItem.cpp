#include "FluVNavigationMenuItem.h"
#include "../Utils/FluUtils.h"
#include <QPropertyAnimation>

FluVNavigationMenuItem::FluVNavigationMenuItem(QWidget *parent /*= nullptr*/) : FluVNavigationItem(parent)
{
    m_itemType = FluVNavigationItemType::Menu;

    m_layout = new QHBoxLayout(this);

    m_wrapWidget1 = new QWidget;
    m_wrapWidget2 = new QWidget;

    m_wrapWidgetLayout1 = new QHBoxLayout;
    m_wrapWidgetLayout1->setSpacing(0);
    m_wrapWidget1->setLayout(m_wrapWidgetLayout1);
    m_wrapWidgetLayout1->setContentsMargins(4, 2, 4, 2);

    m_wrapWidget1->setObjectName("wrapWidget1");
    m_wrapWidget2->setObjectName("wrapWidget2");

    m_menuButton = new QPushButton;
    m_menuButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::GlobalNavButton));
    m_menuButton->setIconSize(QSize(20, 20));
    m_menuButton->setFixedSize(24, 24);
    m_wrapWidget1->setFixedWidth(40);

    m_wrapWidgetLayout1->addWidget(m_menuButton);

    m_layout->setSpacing(0);
    m_layout->addWidget(m_wrapWidget1);
    m_layout->addSpacing(12);
    m_layout->addWidget(m_wrapWidget2, 1);
    // m_layout->setSpacing(0);
    // m_layout->setContentsMargins(0, 4, 0, 4);
    m_layout->setContentsMargins(0, 0, 0, 0);

    m_wrapWidget1->setFixedHeight(30);
    m_wrapWidget2->setFixedHeight(30);
    setFixedHeight(30);
    setFixedWidth(180);

    m_menuButton->setObjectName("menuButton");

    connect(m_menuButton, &QPushButton::clicked, [=](bool b) { emit menuItemClicked(); });

    onThemeChanged();
}

void FluVNavigationMenuItem::setItemWidth(int width)
{
    setFixedWidth(width);
}

void FluVNavigationMenuItem::setItemHeight(int height)
{
    // setFixedHeight(height);
    int itemHeight = height - m_layout->contentsMargins().top() - m_layout->contentsMargins().bottom();
    m_wrapWidget1->setFixedHeight(itemHeight);
    m_wrapWidget2->setFixedHeight(itemHeight);
    setFixedHeight(height);
}

void FluVNavigationMenuItem::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluVNavigationMenuItem::onThemeChanged()
{
    m_menuButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::GlobalNavButton, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUtils::setQssByFileName("FluVNavigationMenuItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
