#include "FluAppBarToggleButton.h"

FluAppBarToggleButton::FluAppBarToggleButton(FluAwesomeType awesomeType, QWidget* parent /*= nullptr*/) : FluWidget(parent), m_awesomeType(awesomeType), m_bToggled(false)
{
    m_vMainLayout = new QVBoxLayout;
    setLayout(m_vMainLayout);

    // m_vMainLayout->setContentsMargins(5, 5, 5, 5);
    m_vMainLayout->setAlignment(Qt::AlignHCenter);

    setFixedSize(70, 50);

    // icon and text;
    m_iconBtn = new QPushButton;
    // m_iconBtn->setFixedSize(25, 25);
    m_iconBtn->setIconSize(QSize(20, 20));
    m_iconBtn->setObjectName("iconBtn");
    m_vMainLayout->addWidget(m_iconBtn);

    m_textLabel = new QLabel;
    m_textLabel->setObjectName("textLabel");
    m_vMainLayout->addWidget(m_textLabel);

    m_iconBtn->setIcon(FluIconUtils::getFluentIconPixmap(awesomeType, FluThemeUtils::getUtils()->getTheme()));

    setToggled(m_bToggled);

    connect(m_iconBtn, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(this, &FluAppBarToggleButton::clicked, [=]() {
        m_bToggled = !m_bToggled;
        setToggled(m_bToggled);

        updateIcon();

        update();
    });

    onThemeChanged();
}

void FluAppBarToggleButton::updateIcon()
{
    if (FluThemeUtils::isLightTheme())
    {
        if (m_bToggled)
        {
            m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Dark));
        }
        else
        {
            m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Light));
        }
    }
    else
    {
        if (m_bToggled)
        {
            m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Light));
        }
        else
        {
            m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Dark));
        }
    }
}

void FluAppBarToggleButton::setAwesomeType(FluAwesomeType awesomeType)
{
    m_awesomeType = awesomeType;
}

FluAwesomeType FluAppBarToggleButton::getAwesomeType()
{
    return m_awesomeType;
}

void FluAppBarToggleButton::setText(QString text)
{
    m_textLabel->setText(text);
}

QString FluAppBarToggleButton::getText()
{
    return m_textLabel->text();
}

void FluAppBarToggleButton::setToggled(bool bToggled)
{
    m_bToggled = bToggled;

    setProperty("toggled", m_bToggled);
    m_textLabel->setProperty("toggled", m_bToggled);
    m_iconBtn->setProperty("toggled", m_bToggled);
    style()->polish(this);
    m_textLabel->style()->polish(m_textLabel);
    m_iconBtn->style()->polish(m_iconBtn);
}

bool FluAppBarToggleButton::getToggled()
{
    return m_bToggled;
}

void FluAppBarToggleButton::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
    emit clicked();
}

void FluAppBarToggleButton::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluAppBarToggleButton::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluAppBarToggleButton.qss", this, FluThemeUtils::getUtils()->getTheme());
    updateIcon();
}
