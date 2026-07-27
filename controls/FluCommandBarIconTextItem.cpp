#include "FluCommandBarIconTextItem.h"
#include <QStyleOption>
#include <QStyle>
#include <QPainter>
#include "FluCommandBarItemType.h"

FluCommandBarIconTextItem::FluCommandBarIconTextItem(QWidget* parent) : FluCommandBarItem(parent), m_awesomeType(FluAwesomeType::None)
{
    m_itemType = FluCommandBarItemType::iconText;

    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(5);
    setLayout(m_mainLayout);

    m_iconButton = new QPushButton;
    m_iconButton->setIconSize(QSize(16, 16));
    m_iconButton->setObjectName("iconBtn");
    m_mainLayout->addWidget(m_iconButton);

    m_textLabel = new QLabel;
    m_textLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_textLabel->setObjectName("textLabel");
    m_mainLayout->addWidget(m_textLabel);

    m_roundMenu = new FluRoundMenu("", FluAwesomeType::None, this);

    setFixedHeight(26);
    onThemeChanged();
    connect(m_iconButton, &QPushButton::clicked, this, [=]() { emit clicked(); });
    connect(this, &FluCommandBarIconTextItem::clicked, this, [=]() {
        if (m_roundMenu->actions().isEmpty())
            return;

        showAtBottomLeft();
    });
}

FluCommandBarIconTextItem::FluCommandBarIconTextItem(FluAwesomeType type, QString text, QWidget* parent) : FluCommandBarIconTextItem(parent)
{
    m_awesomeType = type;
    m_iconButton->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluThemeUtils::getUtils()->getTheme()));
    m_textLabel->setText(text);
}

void FluCommandBarIconTextItem::showAtBottomLeft()
{
    QPoint leftBottomPos = rect().bottomLeft();
    leftBottomPos = mapToGlobal(leftBottomPos);
    m_roundMenu->exec(leftBottomPos);
}

void FluCommandBarIconTextItem::showAtBottomRight()
{
    QPoint rightBottomPos = rect().bottomRight();
    rightBottomPos.setX(rightBottomPos.x() - m_roundMenu->width());

    // map to global;
    rightBottomPos = mapToGlobal(rightBottomPos);

    m_roundMenu->exec(rightBottomPos);
}

void FluCommandBarIconTextItem::showAtBottomCenter()
{
    QPoint rightBottomPos = rect().bottomRight();
    rightBottomPos.setX(rightBottomPos.x() - m_roundMenu->width() / 2 - width() / 2);

    // map to global;
    rightBottomPos = mapToGlobal(rightBottomPos);
    m_roundMenu->exec(rightBottomPos);
}

void FluCommandBarIconTextItem::mouseReleaseEvent(QMouseEvent* event)
{
    FluCommandBarItem::mouseReleaseEvent(event);
    emit clicked();
}

void FluCommandBarIconTextItem::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluCommandBarIconTextItem::onThemeChanged()
{
    m_iconButton->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUtils::setQssByFileName("FluCommandBarIconTextItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
