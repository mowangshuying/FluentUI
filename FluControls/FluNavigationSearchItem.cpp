#include "FluNavigationSearchItem.h"

FluNavigationSearchItem::FluNavigationSearchItem(QWidget* parent /*= nullptr*/) : FluNavigationItem(parent)
{
    m_itemType = FluNavigationItemType::Search;
    // long is search edit
    // short is search button

    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setContentsMargins(0, 4, 0, 4);
    setLayout(m_hMainLayout);

    m_searchLineEdit = new FluSearchLineEdit;
    m_searchLineEdit->setObjectName("searchLineEdit");
    m_searchButton = new QPushButton;
    m_searchButton->setFixedSize(44, 40);
    m_searchButton->setObjectName("searchButton");
    m_searchButton->setIconSize(QSize(24, 24));
    m_searchButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search));

    m_hMainLayout->addWidget(m_searchButton);
    m_hMainLayout->addSpacing(8);
    m_hMainLayout->addWidget(m_searchLineEdit);
    hideSearchButton();

    setFixedHeight(40);
    // m_searchLineEdit->setFixedWidth(300);
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNavigationSearchItem.qss", this);
    // connect(this, &FluNavigationSearchItem::itemClicked, this, &FluNavigationSearchItem::onItemClicked);
    connect(m_searchButton, &QPushButton::clicked, [=]() { emit itemClicked(); });
    
}

void FluNavigationSearchItem::onItemClicked()
{
}

void FluNavigationSearchItem::onThemeChanged()
{
    if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
    {
        m_searchButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search, QColor(8, 8, 8)));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNavigationSearchItem.qss", this);
    }
    else
    {
        m_searchButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search, QColor(239, 239, 239)));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluNavigationSearchItem.qss", this);
    }
}
