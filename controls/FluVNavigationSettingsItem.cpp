#include "FluVNavigationSettingsItem.h"
#include "FluVNavigationView.h"

FluVNavigationSettingsItem::FluVNavigationSettingsItem(QIcon icon, QString text, QWidget* parent /*= nullptr*/) : FluVNavigationItem(parent)
{
    m_itemType = FluVNavigationItemType::Setting;
    setFixedSize(180, 30);
    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);

    m_mainLayout->setContentsMargins(0, 2, 0, 2);

    m_indicator = new FluVNavigationIndicator(this);
    m_icon = new FluRotationButton(this);
    m_label = new QLabel;
    m_label->setText(text);

    m_indicator->setFixedHeight(14);
    m_indicator->setFixedWidth(3);
    m_icon->setFixedSize(24, 24);
    m_label->setWordWrap(true);

    m_icon->setIconSize(QSize(20, 20));
    m_icon->setIcon(icon);

    m_indicator->setObjectName("indicator");
    m_icon->setObjectName("icon");
    m_label->setObjectName("label");

    m_mainLayout->addSpacing(4);
    m_mainLayout->addWidget(m_indicator);
    m_mainLayout->addWidget(m_icon);
    m_mainLayout->addSpacing(12);
    m_mainLayout->addWidget(m_label, 1);
    m_mainLayout->setSpacing(0);

    onThemeChanged();
    connect(m_icon, &FluRotationButton::clicked, [=](bool b) { emit itemClicked(); });
    connect(this, &FluVNavigationSettingsItem::itemClicked, this, &FluVNavigationSettingsItem::onItemClicked);
}

FluVNavigationSettingsItem::FluVNavigationSettingsItem(FluAwesomeType awesomeType, QString text, QWidget* parent) : FluVNavigationSettingsItem(QIcon(), text, parent)
{
    m_icon->setIcon(FluIconUtils::getFluentIcon(awesomeType, FluThemeUtils::getUtils()->getTheme()));
    m_icon->setAwesomeType(awesomeType);
}

void FluVNavigationSettingsItem::setItemWidth(int width)
{
    setFixedWidth(width);
}

void FluVNavigationSettingsItem::setItemHeight(int height)
{
    setFixedHeight(height);
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
    m_icon->style()->polish(m_icon);
    m_label->style()->polish(m_label);
}

void FluVNavigationSettingsItem::updateSelected(bool b)
{
    m_isSelected = b;
    setProperty("selected", b);
    m_indicator->setSelected(b);
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
    FluStyleSheetUtils::setQssByFileName("FluVNavigationSettingsItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
