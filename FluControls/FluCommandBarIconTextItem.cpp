#include "FluCommandBarIconTextItem.h"
#include <QStyleOption>
#include <QStyle>
#include <QPainter>
#include "FluCommandBarItemType.h"

FluCommandBarIconTextItem::FluCommandBarIconTextItem(QWidget* parent) : FluCommandBarItem(parent), m_awesomeType(FluAwesomeType::None)
{
    m_itemType = FluCommandBarItemType::iconText;

    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setContentsMargins(0, 0, 0, 0);
    m_hMainLayout->setSpacing(5);
    setLayout(m_hMainLayout);

    m_iconBtn = new QPushButton;
    m_iconBtn->setIconSize(QSize(16, 16));
    m_iconBtn->setObjectName("iconBtn");
    m_hMainLayout->addWidget(m_iconBtn);

    m_textLabel = new QLabel;
    m_textLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_textLabel->setObjectName("textLabel");
    m_hMainLayout->addWidget(m_textLabel);

    m_roundMenu = new FluRoundMenu("", FluAwesomeType::None, this);

    setFixedHeight(26);
    onThemeChanged();
    connect(m_iconBtn, &QPushButton::clicked, this, [=]() { emit clicked(); });
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    connect(this, &FluCommandBarIconTextItem::clicked, this, [=]() {
        if (m_roundMenu->actions().isEmpty())
            return;

        showAtBottomLeft();
    });
}

FluCommandBarIconTextItem::FluCommandBarIconTextItem(FluAwesomeType type, QString text, QWidget* parent) : FluCommandBarIconTextItem(parent)
{
    m_awesomeType = type;
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluThemeUtils::getUtils()->getTheme()));
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
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUitls::setQssByFileName("FluCommandBarIconTextItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
