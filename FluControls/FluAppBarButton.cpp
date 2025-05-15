#include "FluAppBarButton.h"

FluAppBarButton::FluAppBarButton(FluAwesomeType awesomeType, QWidget* parent /*= nullptr*/) : FluWidget(parent), m_awesomeType(awesomeType), m_shortCut(nullptr)
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
    m_textLabel->setAlignment(Qt::AlignHCenter);
    m_textLabel->setObjectName("textLabel");
    m_vMainLayout->addWidget(m_textLabel);

    m_iconBtn->setIcon(FluIconUtils::getFluentIconPixmap(awesomeType, FluThemeUtils::getUtils()->getTheme()));
    onThemeChanged();
}

void FluAppBarButton::setAwesomeType(FluAwesomeType awesomeType)
{
    m_awesomeType = awesomeType;
}

FluAwesomeType FluAppBarButton::getAwesomeType()
{
    return m_awesomeType;
}

void FluAppBarButton::setText(QString text)
{
    m_textLabel->setText(text);
}

QString FluAppBarButton::getText()
{
    return m_textLabel->text();
}

void FluAppBarButton::setShortCut(QKeySequence keySequence)
{
    if (m_shortCut != nullptr)
        delete m_shortCut;

    m_shortCut = new QShortcut(this);
    m_shortCut->setKey(keySequence);
    m_shortCut->setContext(Qt::ApplicationShortcut);
    connect(m_shortCut, &QShortcut::activated, [=]() {
        emit clicked();
        LOG_DEBUG << "called";
    });
}

void FluAppBarButton::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
    emit clicked();
}

void FluAppBarButton::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluAppBarButton::onThemeChanged()
{
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUitls::setQssByFileName("FluAppBarButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}
