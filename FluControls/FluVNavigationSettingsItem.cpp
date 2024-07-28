#include "FluVNavigationSettingsItem.h"
#include "FluVNavigationView.h"

FluVNavigationSettingsItem::FluVNavigationSettingsItem(QIcon icon, QString text, QWidget* parent /*= nullptr*/) : FluVNavigationItem(parent)
{
    m_itemType = FluVNavigationItemType::Setting;
    setFixedSize(320, 40);
    m_hMainLayout = new QHBoxLayout;
    setLayout(m_hMainLayout);

    m_hMainLayout->setContentsMargins(0, 4, 0, 4);

    m_indicator = new QWidget(this);
    m_icon = new FluRotationButton(this);
    m_label = new QLabel;
    m_label->setText(text);

    m_indicator->setFixedHeight(18);
    m_indicator->setFixedWidth(4);
    m_icon->setFixedSize(30, 30);
    m_label->setWordWrap(true);

    m_icon->setIconSize(QSize(24, 24));
    m_icon->setIcon(icon);

    m_indicator->setObjectName("indicator");
    m_icon->setObjectName("icon");
    m_label->setObjectName("label");

    m_hMainLayout->addSpacing(4);
    m_hMainLayout->addWidget(m_indicator);
    m_hMainLayout->addWidget(m_icon);
    m_hMainLayout->addSpacing(12);
    m_hMainLayout->addWidget(m_label, 1);
    m_hMainLayout->setSpacing(0);

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVNavigationSettingsItem.qss", this);
    connect(m_icon, &FluRotationButton::clicked, [=](bool b) { emit itemClicked(); });
    connect(this, &FluVNavigationSettingsItem::itemClicked, this, &FluVNavigationSettingsItem::onItemClicked);
}

FluVNavigationSettingsItem::FluVNavigationSettingsItem(FluAwesomeType awesomeType, QString text, QWidget* parent) : FluVNavigationSettingsItem(QIcon(), text, parent)
{
    m_icon->setIcon(FluIconUtils::getFluentIcon(awesomeType));
    m_icon->setAwesomeType(awesomeType);
}

void FluVNavigationSettingsItem::onItemClicked()
{
    // click it and rotation it!
    m_icon->setReserveAngle(16);

    // get parent view and update select
    auto navView = getParentView();
    if (navView == nullptr)
        return;
    navView->clearAllItemsSelectState();
    updateSelected(true);
    navView->updateAllItemsStyleSheet();
}

void FluVNavigationSettingsItem::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVNavigationSettingsItem.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluVNavigationSettingsItem.qss", this);
    }
}
