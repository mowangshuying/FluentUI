#include "FluMSNavigationItem.h"

FluMSNavigationItem::FluMSNavigationItem(QWidget* parent /*= nullptr*/) : FluWidget(parent), m_awesomeType(FluAwesomeType::None)
{
    m_hMainLayout = new QHBoxLayout;
    setLayout(m_hMainLayout);

    m_hMainLayout->setAlignment(Qt::AlignHCenter);
    m_hMainLayout->setSpacing(0);
    setFixedSize(65, 60);

    m_indicatorLabel = new QLabel;
    m_indicatorLabel->setFixedWidth(3);
    m_hMainLayout->addWidget(m_indicatorLabel);

    m_vLayout = new QVBoxLayout;
    m_hMainLayout->addLayout(m_vLayout);

    m_iconBtn = new QPushButton;
    m_iconBtn->setFixedSize(40, 40);
    m_iconBtn->setIconSize(QSize(40,40));
    m_iconBtn->setObjectName("iconBtn");
    m_vLayout->addWidget(m_iconBtn);

    m_textLabel = new QLabel;
    m_textLabel->setAlignment(Qt::AlignHCenter);
    m_textLabel->setObjectName("textLabel");
    m_vLayout->addWidget(m_textLabel);

    onThemeChanged();
}

FluMSNavigationItem::FluMSNavigationItem(FluAwesomeType awesomeType, QString text, QString key, QWidget* parent /*= nullptr*/) : FluMSNavigationItem(parent)
{
    setAwesomeType(awesomeType);
    setText(text);
    setKey(key);
    onThemeChanged();
}

void FluMSNavigationItem::setAwesomeType(FluAwesomeType type)
{
    m_awesomeType = type;
}

FluAwesomeType FluMSNavigationItem::getAwesomeType()
{
    return m_awesomeType;
}

void FluMSNavigationItem::setText(QString text)
{
    m_textLabel->setText(text);
}

QString FluMSNavigationItem::getText()
{
    return m_textLabel->text();
}

void FluMSNavigationItem::setKey(QString key)
{
    m_Key = key;
}

QString FluMSNavigationItem::getKey()
{
    return m_Key;
}

void FluMSNavigationItem::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
    emit clicked();
}

void FluMSNavigationItem::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluMSNavigationItem::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Light));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMSNavigationItem.qss", this);
    }
    else
    {
        m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Dark));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluMSNavigationItem.qss", this);
    }
}
