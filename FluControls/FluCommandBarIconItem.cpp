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

    m_roundMenu = new FluRoundMenu("", FluAwesomeType::None, this);

    setFixedHeight(36);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    connect(this, &FluCommandBarIconItem::clicked, this, [=]() {
        if (m_roundMenu->actions().isEmpty())
            return;

        showAtBottomCenter();
    });

    connect(m_iconBtn, &QPushButton::clicked, this, [=]() { emit clicked(); });
}

FluCommandBarIconItem::FluCommandBarIconItem(FluAwesomeType type, QWidget* parent) : FluCommandBarIconItem(parent)
{
    m_awesomeType = type;
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluThemeUtils::getUtils()->getTheme()));
}

FluRoundMenu* FluCommandBarIconItem::getRoundMenu()
{
    return m_roundMenu;
}

void FluCommandBarIconItem::setRoundMenu(FluRoundMenu* menu)
{
    m_roundMenu->deleteLater();
    m_roundMenu = menu;
}

void FluCommandBarIconItem::showAtBottomRight()
{
    QPoint rightBottomPos = rect().bottomRight();
    rightBottomPos.setX(rightBottomPos.x() - m_roundMenu->width());

    // map to global;
    rightBottomPos = mapToGlobal(rightBottomPos);

    m_roundMenu->exec(rightBottomPos);
}

void FluCommandBarIconItem::showAtBottomCenter()
{
    QPoint rightBottomPos = rect().bottomRight();
    rightBottomPos.setX(rightBottomPos.x() - m_roundMenu->width() / 2 - width() / 2);

    // map to global;
    rightBottomPos = mapToGlobal(rightBottomPos);
    m_roundMenu->exec(rightBottomPos);
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
