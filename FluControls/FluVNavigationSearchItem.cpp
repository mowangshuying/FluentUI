#include "FluVNavigationSearchItem.h"

FluVNavigationSearchItem::FluVNavigationSearchItem(QWidget* parent /*= nullptr*/) : FluVNavigationItem(parent)
{
    m_itemType = FluVNavigationItemType::Search;
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
    onThemeChanged();
    connect(m_searchButton, &QPushButton::clicked, [=]() { emit itemClicked(); });
}

void FluVNavigationSearchItem::hideSearchButton()
{
    m_searchButton->hide();
    m_searchLineEdit->show();
}

void FluVNavigationSearchItem::hideSearchEdit()
{
    m_searchButton->show();
    m_searchLineEdit->hide();
}

void FluVNavigationSearchItem::mouseReleaseEvent(QMouseEvent* event)
{
    FluVNavigationItem::mouseReleaseEvent(event);
    emit itemClicked();
}

void FluVNavigationSearchItem::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluVNavigationSearchItem::onItemClicked()
{
}

void FluVNavigationSearchItem::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_searchButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search, QColor(8, 8, 8)));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVNavigationSearchItem.qss", this);
    }
    else
    {
        m_searchButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search, QColor(239, 239, 239)));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluVNavigationSearchItem.qss", this);
    }
}
