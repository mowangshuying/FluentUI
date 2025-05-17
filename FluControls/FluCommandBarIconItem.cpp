#include "FluCommandBarIconItem.h"

FluCommandBarIconItem::FluCommandBarIconItem(QWidget* parent) : FluCommandBarItem(parent)
{
    m_itemType = FluCommandBarItemType::icon;
    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setSpacing(0);
    setLayout(m_hMainLayout);

    m_iconBtn = new QPushButton;
    m_iconBtn->setIconSize(QSize(25, 25));
    m_iconBtn->setObjectName("iconBtn");
    m_hMainLayout->addWidget(m_iconBtn);

    setFixedHeight(36);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluCommandBarIconItem::FluCommandBarIconItem(FluAwesomeType type, QWidget* parent) : FluCommandBarIconItem(parent)
{
    m_awesomeType = type;
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluThemeUtils::getUtils()->getTheme()));
}

void FluCommandBarIconItem::mouseReleaseEvent(QMouseEvent* event)
{
    FluCommandBarItem::mouseReleaseEvent(event);
    emit clicked();
}

void FluCommandBarIconItem::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
