#include "FluNavigationMenuItem.h"
#include "../FluUtils/FluUtils.h"

FluNavigationMenuItem::FluNavigationMenuItem(QWidget *parent /*= nullptr*/) : FluNavigationItem(parent)
{
    m_hLayout = new QHBoxLayout(this);

    m_menuButton = new QPushButton(this);
    m_menuButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::GlobalNavButton));
    m_menuButton->setIconSize(QSize(15, 15));
    m_menuButton->setFixedSize(30, 30);
    m_hLayout->setContentsMargins(10, 0, 0, 0);

    setFixedHeight(40);
    setFixedWidth(320);

    m_hLayout->addWidget(m_menuButton);
    m_hLayout->addStretch(1);
    m_menuButton->setObjectName("menuButton");
    QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluNavigationMenuItem.qss");
    setStyleSheet(qss);
    connect(m_menuButton, &QPushButton::clicked, [=](bool b) { emit menuItemClicked(); });
}
