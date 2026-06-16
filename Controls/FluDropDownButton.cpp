#include "FluDropDownButton.h"

FluDropDownButton::FluDropDownButton(QWidget* parent /*= nullptr*/) : FluWidget(parent), m_svgDarkPath(""), m_svgLightPath("")
{
    m_textAwesomeType = FluAwesomeType::None;
    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setContentsMargins(3, 3, 3, 3);
    m_hMainLayout->setSpacing(0);

    setLayout(m_hMainLayout);

    // add text and icon
    m_textBtn = new QPushButton;
    m_iconBtn = new QPushButton;

    m_textBtn->setObjectName("textBtn");
    m_iconBtn->setObjectName("iconBtn");

    m_iconBtn->setFixedSize(24, 24);
    m_textBtn->setFixedHeight(24);

    m_iconBtn->setFixedSize(24, 24);
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));

    m_hMainLayout->addWidget(m_textBtn, 1);
    m_hMainLayout->addSpacing(3);
    m_hMainLayout->addWidget(m_iconBtn);
    setFixedHeight(30);

    m_menu = new FluMenu;

    connect(m_textBtn, &QPushButton::clicked, [=](bool b) { emit clicked(); });
    connect(m_iconBtn, &QPushButton::clicked, [=](bool b) { emit clicked(); });
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

QPushButton* FluDropDownButton::getTextBtn()
{
    return m_textBtn;
}

QPushButton* FluDropDownButton::getIconBtn()
{
    return m_iconBtn;
}

void FluDropDownButton::setIcon(FluAwesomeType type)
{
    m_textAwesomeType = type;
    m_textBtn->setIconSize(QSize(18, 18));
    m_textBtn->setIcon(FluIconUtils::getFluentIconPixmap(type, FluThemeUtils::getUtils()->getTheme()));
}

void FluDropDownButton::setIcon(QIcon icon)
{
    m_textBtn->setIconSize(QSize(18, 18));
    m_textBtn->setIcon(icon);
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
    m_textBtn->setText(text);
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
        m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluTheme::Light));
        if (m_textAwesomeType != FluAwesomeType::None)
            m_textBtn->setIcon(FluIconUtils::getFluentIcon(m_textAwesomeType, FluTheme::Light));
        if (m_svgLightPath != "")
            m_textBtn->setIcon(FluIconUtils::getSvgIcon(m_svgLightPath));
        //  FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDropDownButton.qss", this);
    }
    else
    {
        m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluTheme::Dark));
        if (m_textAwesomeType != FluAwesomeType::None)
            m_textBtn->setIcon(FluIconUtils::getFluentIcon(m_textAwesomeType, FluTheme::Dark));
        if (m_svgDarkPath != "")
            m_textBtn->setIcon(FluIconUtils::getSvgIcon(m_svgDarkPath));

        //  FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluDropDownButton.qss", this);
    }
    FluStyleSheetUitls::setQssByFileName("FluDropDownButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}
