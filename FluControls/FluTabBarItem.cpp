#include "FluTabBarItem.h"
#include "FluHSplitLine.h"

FluTabBarItem::FluTabBarItem(QWidget* parent /*= nullptr*/)
{
    m_hMainLayout = new QHBoxLayout;
    setLayout(m_hMainLayout);
    m_hMainLayout->setContentsMargins(0, 0, 0, 0);
    m_hMainLayout->setSpacing(0);

    m_iconBtn = new QPushButton(this);
    m_textBtn = new QPushButton(this);
    m_closeBtn = new QPushButton(this);

    m_iconBtn->setFixedSize(20, 20);
    m_closeBtn->setFixedSize(24, 16);

    m_iconBtn->setIconSize(QSize(20, 20));
    m_closeBtn->setIconSize(QSize(12, 12));
    m_textBtn->setFixedHeight(30);
    m_textBtn->setText("Document");

    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Document, FluThemeUtils::getUtils()->getTheme()));
    m_closeBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));

    m_iconBtn->setObjectName("iconBtn");
    m_textBtn->setObjectName("textBtn");
    m_closeBtn->setObjectName("closeBtn");

    m_hMainLayout->addWidget(m_iconBtn);
    m_hMainLayout->addWidget(m_textBtn);
    m_hMainLayout->addWidget(m_closeBtn);

    m_hMainLayout->addSpacing(5);

    setFixedHeight(35);
    connect(m_iconBtn, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(m_textBtn, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(m_closeBtn, &QPushButton::clicked, [=]() { emit clickedCloseBtn(this); });
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { 
        onThemeChanged();
    });
}

void FluTabBarItem::setSelected(bool bSel)
{
    m_bSel = bSel;
    setProperty("selected", bSel);
    m_closeBtn->setProperty("selected", bSel);
    m_closeBtn->style()->polish(m_closeBtn);

    m_closeBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::None, FluThemeUtils::getUtils()->getTheme()));
    if (bSel)
    {
        m_closeBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
    }
}

bool FluTabBarItem::getSelected()
{
    return m_bSel;
}

void FluTabBarItem::setText(QString text)
{
    adjustWidgetSize();
    m_textBtn->setText(text);
}

QString FluTabBarItem::getText()
{
    return m_textBtn->text();
    //adjustWidgetSize();
}

int FluTabBarItem::getWidgetWidth()
{
    QFontMetrics metrics(m_textBtn->font());
    QRect textRect = metrics.boundingRect(m_textBtn->text());
    int textWidth = textRect.width();
    //m_textBtn->setFixedWidth(textWidth);

    // adjust the whole widget width
    int totalWidth = m_iconBtn->width() + textWidth + m_closeBtn->width() + m_hMainLayout->spacing() * 2 + 5;
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
    // m_closeBtn->setProperty("tabBarItemHover", true);

    m_closeBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
}

void FluTabBarItem::leaveEvent(QEvent* event)
{
    // m_closeBtn->setProperty("tabBarItemHover", false);
    if (m_bSel)
        return;

    m_closeBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::None, FluThemeUtils::getUtils()->getTheme()));
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
    FluStyleSheetUitls::setQssByFileName("FluTabBarItem.qss", this, FluThemeUtils::getUtils()->getTheme());
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Document, FluThemeUtils::getUtils()->getTheme()));
    m_closeBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
}
