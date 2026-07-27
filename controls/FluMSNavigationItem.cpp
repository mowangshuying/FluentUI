#include "FluMSNavigationItem.h"
#include "FluMSNavigationView.h"

FluMSNavigationItem::FluMSNavigationItem(QWidget* parent /*= nullptr*/) : FluWidget(parent), m_awesomeType(FluAwesomeType::None)
{
    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);

    m_mainLayout->setAlignment(Qt::AlignHCenter);
    m_mainLayout->setSpacing(0);
    setFixedSize(65, 60);

    m_indicatorLabel = new QLabel;
    m_indicatorLabel->setObjectName("indicatorLabel");
    m_indicatorLabel->setFixedWidth(4);
    m_indicatorLabel->setFixedHeight(26);
    m_mainLayout->addWidget(m_indicatorLabel);
    m_mainLayout->addSpacing(3);

    m_layout = new QVBoxLayout;
    m_mainLayout->addLayout(m_layout);

    m_iconButton = new QPushButton;
    m_iconButton->setFixedSize(40, 40);
    m_iconButton->setIconSize(QSize(40, 40));
    m_iconButton->setObjectName("iconBtn");
    m_layout->addWidget(m_iconButton);

    m_textLabel = new QLabel;
    m_textLabel->setAlignment(Qt::AlignHCenter);
    m_textLabel->setObjectName("textLabel");
    m_layout->addWidget(m_textLabel);

    onThemeChanged();
    // connect(this, &FluMSNavigationItem::clicked, this, [=]() { onItemClicked(); });
}

FluMSNavigationItem::FluMSNavigationItem(FluAwesomeType awesomeType, QString text, QString key, QWidget* parent /*= nullptr*/) : FluMSNavigationItem(parent)
{
    setAwesomeType(awesomeType);
    setText(text);
    setKey(key);
    onThemeChanged();
    connect(this, &FluMSNavigationItem::clicked, this, [=]() { onItemClicked(); });
    connect(m_iconButton, &QPushButton::clicked, this, [=]() { emit clicked(); });
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

void FluMSNavigationItem::setSelected(bool isSelected)
{
    m_isSelected = isSelected;
    setProperty("selected", m_isSelected);
    m_indicatorLabel->setProperty("selected", m_isSelected);

    m_indicatorLabel->style()->polish(m_indicatorLabel);
    style()->polish(this);
}

bool FluMSNavigationItem::getSelected()
{
    return m_isSelected;
}

void FluMSNavigationItem::setParentView(FluMSNavigationView* parentView)
{
    m_parentView = parentView;
}

FluMSNavigationView* FluMSNavigationItem::getParentView()
{
    return m_parentView;
}

void FluMSNavigationItem::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
    LOG_DEBUG << "click item:" << getText();
    emit clicked();
}

void FluMSNavigationItem::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluMSNavigationItem::onItemClicked()
{
    auto parentView = getParentView();
    if (parentView == nullptr)
        return;

    parentView->setSelectedItem(this);
}

void FluMSNavigationItem::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_iconButton->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Light));
        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/light/FluMSNavigationItem.qss", this);
    }
    else
    {
        m_iconButton->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Dark));
        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/dark/FluMSNavigationItem.qss", this);
    }
    FluStyleSheetUtils::setQssByFileName("FluMSNavigationItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
