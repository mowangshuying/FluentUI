#include "FluAppBarToggleButton.h"

FluAppBarToggleButton::FluAppBarToggleButton(FluAwesomeType awesomeType, QWidget* parent /*= nullptr*/) : FluWidget(parent), m_awesomeType(awesomeType), m_isToggled(false)
{
    m_mainLayout = new QVBoxLayout;
    setLayout(m_mainLayout);

    // m_mainLayout->setContentsMargins(5, 5, 5, 5);
    m_mainLayout->setAlignment(Qt::AlignHCenter);

    setFixedSize(70, 50);

    // icon and text;
    m_iconButton = new QPushButton;
    // m_iconButton->setFixedSize(25, 25);
    m_iconButton->setIconSize(QSize(20, 20));
    m_iconButton->setObjectName("iconBtn");
    m_mainLayout->addWidget(m_iconButton);

    m_textLabel = new QLabel;
    m_textLabel->setObjectName("textLabel");
    m_mainLayout->addWidget(m_textLabel);

    m_iconButton->setIcon(FluIconUtils::getFluentIconPixmap(awesomeType, FluThemeUtils::getUtils()->getTheme()));

    setToggled(m_isToggled);

    connect(m_iconButton, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(this, &FluAppBarToggleButton::clicked, [=]() {
        m_isToggled = !m_isToggled;
        setToggled(m_isToggled);

        updateIcon();

        update();
    });

    onThemeChanged();
}

void FluAppBarToggleButton::updateIcon()
{
    if (FluThemeUtils::isLightTheme())
    {
        if (m_isToggled)
        {
            m_iconButton->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Dark));
        }
        else
        {
            m_iconButton->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Light));
        }
    }
    else
    {
        if (m_isToggled)
        {
            m_iconButton->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Light));
        }
        else
        {
            m_iconButton->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Dark));
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

void FluAppBarToggleButton::setToggled(bool isToggled)
{
    m_isToggled = isToggled;

    setProperty("toggled", m_isToggled);
    m_textLabel->setProperty("toggled", m_isToggled);
    m_iconButton->setProperty("toggled", m_isToggled);
    style()->polish(this);
    m_textLabel->style()->polish(m_textLabel);
    m_iconButton->style()->polish(m_iconButton);
}

bool FluAppBarToggleButton::getToggled()
{
    return m_isToggled;
}

void FluAppBarToggleButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (!isEnabled())
        return;
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
    FluStyleSheetUtils::setQssByFileName("FluAppBarToggleButton.qss", this, FluThemeUtils::getUtils()->getTheme());
    updateIcon();
}

void FluAppBarToggleButton::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    m_iconButton->setEnabled(enabled);
    m_textLabel->setEnabled(enabled);
}
