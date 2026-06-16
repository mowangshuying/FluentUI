#include "FluHNavigationSettingsItem.h"

FluHNavigationSettingsItem::FluHNavigationSettingsItem(QWidget* parent /*= nullptr*/) : FluHNavigationItem(parent)
{
    m_hMainLayout = new QHBoxLayout;
    setLayout(m_hMainLayout);

    m_hMainLayout->setContentsMargins(0, 0, 0, 0);

    m_icon = new FluRotationButton(FluAwesomeType::Settings);
    m_icon->setFixedSize(40, 40);
    m_icon->setIconSize(QSize(24, 24));
    m_icon->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Settings));
    m_hMainLayout->addWidget(m_icon);

    onThemeChanged();
}

FluHNavigationSettingsItem::FluHNavigationSettingsItem(FluAwesomeType awesomeType, QWidget* parent /*= nullptr*/) : FluHNavigationSettingsItem(parent)
{
    m_awesomeType = awesomeType;
    m_icon->setAwesomeType(awesomeType);
    onThemeChanged();
}

void FluHNavigationSettingsItem::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluHNavigationSettingsItem::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluHNavigationSettingsItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
