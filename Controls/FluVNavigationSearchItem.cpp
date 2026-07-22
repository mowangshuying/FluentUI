#include "FluVNavigationSearchItem.h"

FluVNavigationSearchItem::FluVNavigationSearchItem(QWidget* parent /*= nullptr*/) : FluVNavigationItem(parent)
{
    m_itemType = FluVNavigationItemType::Search;

    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setContentsMargins(0, 2, 0, 2);
    setLayout(m_mainLayout);

    m_autoSuggestBox = new FluAutoSuggestBox(true);
    m_autoSuggestBox->setFixedHeight(26);
    m_autoSuggestBox->setObjectName("autoSuggestBox");
    m_searchButton = new QPushButton;
    m_searchButton->setFixedSize(36, 26);
    m_searchButton->setObjectName("searchButton");
    m_searchButton->setIconSize(QSize(20, 20));
    m_searchButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search, FluThemeUtils::getUtils()->getTheme()));

    m_mainLayout->addWidget(m_searchButton);
    m_mainLayout->addSpacing(8);
    m_mainLayout->addWidget(m_autoSuggestBox);
    hideSearchButton();

    setFixedHeight(30);
    onThemeChanged();
    connect(m_searchButton, &QPushButton::clicked, [=]() { emit itemClicked(); });
    connect(m_autoSuggestBox, &FluAutoSuggestBox::currentTextChanged, this, [=](QString text) { emit currentTextChanged(text); });
}

void FluVNavigationSearchItem::setItemWidth(int width)
{
    setFixedWidth(width);
}

void FluVNavigationSearchItem::setItemHeight(int height)
{
    setFixedHeight(height);
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
    FluStyleSheetUtils::setQssByFileName("FluVNavigationSearchItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
