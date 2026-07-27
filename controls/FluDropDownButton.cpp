#include "FluDropDownButton.h"

FluDropDownButton::FluDropDownButton(QWidget* parent /*= nullptr*/) : FluWidget(parent), m_svgDarkPath(""), m_svgLightPath("")
{
    m_textAwesomeType = FluAwesomeType::None;
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setContentsMargins(3, 3, 3, 3);
    m_mainLayout->setSpacing(0);

    setLayout(m_mainLayout);

    // add text and icon
    m_textButton = new QPushButton;
    m_iconButton = new QPushButton;

    m_textButton->setObjectName("textBtn");
    m_iconButton->setObjectName("iconBtn");

    m_iconButton->setFixedSize(24, 24);
    m_textButton->setFixedHeight(24);

    m_iconButton->setFixedSize(24, 24);
    m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));

    m_mainLayout->addWidget(m_textButton, 1);
    m_mainLayout->addSpacing(3);
    m_mainLayout->addWidget(m_iconButton);
    setFixedHeight(30);

    m_menu = new FluMenu;

    connect(m_textButton, &QPushButton::clicked, [=](bool b) { emit clicked(); });
    connect(m_iconButton, &QPushButton::clicked, [=](bool b) { emit clicked(); });
    connect(this, &FluDropDownButton::clicked, [=]() {
        if (m_menu->actions().isEmpty())
            return;

        QPoint leftBottomPos = rect().bottomLeft();
        leftBottomPos = mapToGlobal(leftBottomPos);
        leftBottomPos.setY(leftBottomPos.y() + 3);
        m_menu->exec(leftBottomPos);
        //  m_menu->show();
    });

    onThemeChanged();
}

QPushButton* FluDropDownButton::getTextButton()
{
    return m_textButton;
}

QPushButton* FluDropDownButton::getIconButton()
{
    return m_iconButton;
}

void FluDropDownButton::setIcon(FluAwesomeType type)
{
    m_textAwesomeType = type;
    m_textButton->setIconSize(QSize(18, 18));
    m_textButton->setIcon(FluIconUtils::getFluentIconPixmap(type, FluThemeUtils::getUtils()->getTheme()));
}

void FluDropDownButton::setIcon(QIcon icon)
{
    m_textButton->setIconSize(QSize(18, 18));
    m_textButton->setIcon(icon);
}

void FluDropDownButton::setSvgPath(QString svgLightPath, QString svgDarkPath)
{
    m_svgLightPath = svgLightPath;
    m_svgDarkPath = svgDarkPath;
#ifdef USE_QRC
    m_svgDarkPath = m_svgDarkPath.replace("../res/", ":/res/");
    m_svgLightPath = m_svgLightPath.replace("../res/", ":/res/");
#endif
}

void FluDropDownButton::setText(QString text)
{
    m_textButton->setText(text);
}

void FluDropDownButton::addTextItem(QString text)
{
    m_menu->addAction(new FluAction(text));
}

void FluDropDownButton::addIconTextItem(FluAwesomeType type, QString text)
{
    m_menu->addAction(new FluAction(type, text));
}

void FluDropDownButton::addIconTextItem(QIcon type, QString text)
{
    m_menu->addAction(new FluAction(type, text));
}

void FluDropDownButton::mouseReleaseEvent(QMouseEvent* e)
{
    if (!isEnabled())
        return;
    emit clicked();
}

void FluDropDownButton::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluDropDownButton::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluTheme::Light));
        if (m_textAwesomeType != FluAwesomeType::None)
            m_textButton->setIcon(FluIconUtils::getFluentIcon(m_textAwesomeType, FluTheme::Light));
        if (m_svgLightPath != "")
            m_textButton->setIcon(FluIconUtils::getSvgIcon(m_svgLightPath));
        //  FluStyleSheetUtils::setQssByFileName("../StyleSheet/light/FluDropDownButton.qss", this);
    }
    else
    {
        m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluTheme::Dark));
        if (m_textAwesomeType != FluAwesomeType::None)
            m_textButton->setIcon(FluIconUtils::getFluentIcon(m_textAwesomeType, FluTheme::Dark));
        if (m_svgDarkPath != "")
            m_textButton->setIcon(FluIconUtils::getSvgIcon(m_svgDarkPath));

        //  FluStyleSheetUtils::setQssByFileName("../StyleSheet/dark/FluDropDownButton.qss", this);
    }
    FluStyleSheetUtils::setQssByFileName("FluDropDownButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluDropDownButton::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    m_textButton->setEnabled(enabled);
    m_iconButton->setEnabled(enabled);
}
