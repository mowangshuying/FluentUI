#include "FluNavigationMenuItem.h"
#include "../FluUtils/FluUtils.h"
#include <QPropertyAnimation>

FluNavigationMenuItem::FluNavigationMenuItem(QWidget *parent /*= nullptr*/) : FluNavigationItem(parent)
{
    m_itemType = FluNavigationItemType::Menu;
    m_hLayout = new QHBoxLayout(this);

    m_menuButton = new QPushButton(this);
    m_menuButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::GlobalNavButton));
    m_menuButton->setIconSize(QSize(24, 24));
    m_menuButton->setFixedSize(30, 30);
    //m_menuButton->setFixedSize(40, 40);
    m_hLayout->setContentsMargins(0, 4, 0, 4);

    setFixedHeight(40);
    setFixedWidth(320);

    m_hLayout->addWidget(m_menuButton);
    m_hLayout->addStretch(1);
    m_menuButton->setObjectName("menuButton");

    connect(m_menuButton, &QPushButton::clicked, [=](bool b) { emit menuItemClicked(); });
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNavigationMenuItem.qss", this);
}

void FluNavigationMenuItem::onThemeChanged()
{
    if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
    {
        m_menuButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::GlobalNavButton, QColor(8, 8, 8)));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNavigationMenuItem.qss", this);
    }
    else
    {
        m_menuButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::GlobalNavButton, QColor(239, 239, 239)));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluNavigationMenuItem.qss", this);
    }
}
