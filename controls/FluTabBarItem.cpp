#include "FluTabBarItem.h"
#include "FluHSplitLine.h"

FluTabBarItem::FluTabBarItem(QWidget* parent /*= nullptr*/)
{
    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_iconButton = new QPushButton(this);
    m_textButton = new QPushButton(this);
    m_closeButton = new QPushButton(this);

    m_iconButton->setFixedSize(20, 20);
    m_closeButton->setFixedSize(24, 16);

    m_iconButton->setIconSize(QSize(20, 20));
    m_closeButton->setIconSize(QSize(12, 12));
    m_textButton->setFixedHeight(30);
    m_textButton->setText("Document");

    m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Document, FluThemeUtils::getUtils()->getTheme()));
    m_closeButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));

    m_iconButton->setObjectName("iconBtn");
    m_textButton->setObjectName("textBtn");
    m_closeButton->setObjectName("closeBtn");

    m_mainLayout->addWidget(m_iconButton);
    m_mainLayout->addWidget(m_textButton);
    m_mainLayout->addWidget(m_closeButton);

    m_mainLayout->addSpacing(5);

    setFixedHeight(35);
    connect(m_iconButton, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(m_textButton, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(m_closeButton, &QPushButton::clicked, [=]() { emit clickedCloseButton(this); });
    onThemeChanged();
}

void FluTabBarItem::setSelected(bool isSel)
{
    m_isSel = isSel;
    setProperty("selected", isSel);
    m_closeButton->setProperty("selected", isSel);
    m_closeButton->style()->polish(m_closeButton);

    m_closeButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::None, FluThemeUtils::getUtils()->getTheme()));
    if (isSel)
    {
        m_closeButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
    }
}

bool FluTabBarItem::getSelected()
{
    return m_isSel;
}

void FluTabBarItem::setText(QString text)
{
    adjustWidgetSize();
    m_textButton->setText(text);
}

QString FluTabBarItem::getText()
{
    return m_textButton->text();
    // adjustWidgetSize();
}

int FluTabBarItem::getWidgetWidth()
{
    QFontMetrics metrics(m_textButton->font());
    QRect textRect = metrics.boundingRect(m_textButton->text());
    int textWidth = textRect.width();
    // m_textButton->setFixedWidth(textWidth);

    // adjust the whole widget width
    int totalWidth = m_iconButton->width() + textWidth + m_closeButton->width() + m_mainLayout->spacing() * 2 + 5;
    return totalWidth;
}

void FluTabBarItem::adjustWidgetSize()
{
    setFixedWidth(getWidgetWidth());
}

void FluTabBarItem::resizeEvent(QResizeEvent* event)
{
    emit sizeChanged();
}

void FluTabBarItem::enterEvent(QEnterEvent* event)
{
    // m_closeButton->setProperty("tabBarItemHover", true);

    m_closeButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
}

void FluTabBarItem::leaveEvent(QEvent* event)
{
    // m_closeButton->setProperty("tabBarItemHover", false);
    if (m_isSel)
        return;

    m_closeButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::None, FluThemeUtils::getUtils()->getTheme()));
}

void FluTabBarItem::mouseReleaseEvent(QMouseEvent* event)
{
    emit clicked();
}

void FluTabBarItem::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluTabBarItem::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluTabBarItem.qss", this, FluThemeUtils::getUtils()->getTheme());
    m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Document, FluThemeUtils::getUtils()->getTheme()));
    m_closeButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
}
