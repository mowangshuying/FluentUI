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

    onThemeChanged();
    connect(m_icon, &FluRotationButton::clicked, [=](bool b) { emit itemClicked(); });
    connect(this, &FluVNavigationSettingsItem::itemClicked, this, &FluVNavigationSettingsItem::onItemClicked);
}

FluVNavigationSettingsItem::FluVNavigationSettingsItem(FluAwesomeType awesomeType, QString text, QWidget* parent) : FluVNavigationSettingsItem(QIcon(), text, parent)
{
    m_icon->setIcon(FluIconUtils::getFluentIcon(awesomeType, FluThemeUtils::getUtils()->getTheme()));
    m_icon->setAwesomeType(awesomeType);
}

QLabel* FluVNavigationSettingsItem::getLabel()
{
    return m_label;
}

void FluVNavigationSettingsItem::hideLabel()
{
    m_label->hide();
}

void FluVNavigationSettingsItem::showLabel()
{
    m_label->show();
}

void FluVNavigationSettingsItem::updateAllItemsStyleSheet()
{
    updateItemsStyleSheet();
}

void FluVNavigationSettingsItem::updateItemsStyleSheet()
{
    style()->polish(this);
    m_indicator->style()->polish(m_indicator);
    m_icon->style()->polish(m_icon);
    m_label->style()->polish(m_label);
}

void FluVNavigationSettingsItem::updateSelected(bool b)
{
    m_bSelected = b;
    setProperty("selected", b);
    m_indicator->setProperty("selected", b);
    m_label->setProperty("selected", b);
}

void FluVNavigationSettingsItem::clearAllItemsSelectState()
{
    updateSelected(false);
}

void FluVNavigationSettingsItem::mouseReleaseEvent(QMouseEvent* event)
{
    FluVNavigationItem::mouseReleaseEvent(event);
    emit itemClicked();
}

void FluVNavigationSettingsItem::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
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
    FluStyleSheetUitls::setQssByFileName("FluVNavigationSettingsItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
