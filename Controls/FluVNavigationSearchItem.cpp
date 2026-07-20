#include "FluVNavigationSearchItem.h"

FluVNavigationSearchItem::FluVNavigationSearchItem(QWidget* parent /*= nullptr*/) : FluVNavigationItem(parent)
{
    m_itemType = FluVNavigationItemType::Search;

    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setContentsMargins(0, 4, 0, 4);
    setLayout(m_hMainLayout);

    m_autoSuggestBox = new FluAutoSuggestBox(true);
    m_autoSuggestBox->setObjectName("autoSuggestBox");
    m_searchButton = new QPushButton;
    m_searchButton->setFixedSize(44, 40);
    m_searchButton->setObjectName("searchButton");
    m_searchButton->setIconSize(QSize(24, 24));
    m_searchButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search, FluThemeUtils::getUtils()->getTheme()));

    m_hMainLayout->addWidget(m_searchButton);
    m_hMainLayout->addSpacing(8);
    m_hMainLayout->addWidget(m_autoSuggestBox);
    hideSearchButton();

    setFixedHeight(40);
    onThemeChanged();
    connect(m_searchButton, &QPushButton::clicked, [=]() { emit itemClicked(); });
    connect(m_autoSuggestBox, &FluAutoSuggestBox::currentTextChanged, this, [=](QString text) { emit currentTextChanged(text); });
}

void FluVNavigationSearchItem::setItemWidth(int nWidth)
{
    setFixedWidth(nWidth);
}

void FluVNavigationSearchItem::setItemHeight(int nHeight)
{
    setFixedHeight(nHeight);
}

void FluVNavigationSearchItem::hideSearchButton()
{
    m_searchButton->hide();
    m_autoSuggestBox->show();
}

void FluVNavigationSearchItem::hideSearchEdit()
{
    m_searchButton->show();
    m_autoSuggestBox->hide();
}

void FluVNavigationSearchItem::updateSearchKeys(std::vector<QString> keys)
{
    m_autoSuggestBox->addKeys(keys);
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
    QIcon icon = FluIconUtils::getFluentIcon(FluAwesomeType::Search, FluThemeUtils::getUtils()->getTheme());
    m_searchButton->setIcon(icon);
    FluStyleSheetUitls::setQssByFileName("FluVNavigationSearchItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
