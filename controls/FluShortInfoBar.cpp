#include "FluShortInfoBar.h"
#include "FluInfoBarMgr.h"
#include <QPointer>

#ifdef _DEBUG
int FluShortInfoBar::m_count = 0;
#endif

FluShortInfoBar::FluShortInfoBar(FluShortInfoBarType infobarType, QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
#ifdef _DEBUG
    m_count++;
    // LOG_DEBUG << "Count = " << m_count;
#endif
    setFixedHeight(50);

    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);

    m_iconLabel = new QLabel;
    m_iconLabel->setFixedSize(18, 18);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setObjectName("iconLabel");
    m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::CheckMark, QColor(239, 239, 239), 18, 18));
    m_mainLayout->addWidget(m_iconLabel);

    m_infoLabel = new QLabel;
    m_infoLabel->setWordWrap(true);
    m_infoLabel->setText(tr("A Short Essential app Message."));
    m_infoLabel->setObjectName("infoLabel");
    m_mainLayout->addWidget(m_infoLabel, 1);

    m_closeButton = new QPushButton;
    m_closeButton->setFixedSize(30, 30);
    m_closeButton->setIconSize(QSize(15, 15));
    m_closeButton->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChromeClose));

    m_closeButton->setObjectName("closeBtn");
    m_mainLayout->addWidget(m_closeButton);

    m_opacityEffect = new QGraphicsOpacityEffect(this);
    m_opacityAni = new QPropertyAnimation(m_opacityEffect, "opacity", this);

    connect(m_closeButton, &QPushButton::clicked, [=]() {
        FluInfoBarMgr::getInstance()->removeInfoBar(this);
        close();
        deleteLater();
    });

    updateInfoBarTypeProperty(infobarType);
    m_disappearDuration = -1;
    m_isDisappearing = false;

    onThemeChanged();
}

FluShortInfoBar::~FluShortInfoBar()
{
#ifdef _DEBUG
    m_count--;
    // LOG_DEBUG << "Count = " << m_count;
    //  disconnect();
    //  FluInfoBarMgr::getInstance()->removeInfoBar(this);
#endif
}

void FluShortInfoBar::setInfoBarTypeProperty(QString infoBarType)
{
    setProperty("infoBarType", infoBarType);
    m_iconLabel->setProperty("infoBarType", infoBarType);
    m_infoLabel->setProperty("infoBarType", infoBarType);
    m_closeButton->setProperty("infoBarType", infoBarType);
    style()->polish(this);
    m_iconLabel->style()->polish(m_iconLabel);
    m_infoLabel->style()->polish(m_infoLabel);
    m_closeButton->style()->polish(m_closeButton);
}

void FluShortInfoBar::setInfoBarType(FluShortInfoBarType type)
{
    updateInfoBarTypeProperty(type);
}

void FluShortInfoBar::setInfoBarText(QString infoBarText)
{
    m_infoLabel->setText(infoBarText);
}

void FluShortInfoBar::updateInfoBarTypeProperty(FluShortInfoBarType infoBarType)
{
    switch (infoBarType)
    {
        case FluShortInfoBarType::Info:
            setInfoBarTypeProperty("Info");
            m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Info, QColor(239, 239, 239), 18, 18));
            break;
        case FluShortInfoBarType::Suc:
            setInfoBarTypeProperty("Suc");
            m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::StatusCircleCheckmark, QColor(239, 239, 239), 18, 18));
            break;
        case FluShortInfoBarType::Warn:
            setInfoBarTypeProperty("Warn");
            m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Info, QColor(239, 239, 239), 18, 18));
            break;
        case FluShortInfoBarType::Error:
            setInfoBarTypeProperty("Error");
            m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Error, QColor(239, 239, 239), 18, 18));
            break;
    }
}

void FluShortInfoBar::disappear()
{
    QPointer<FluShortInfoBar> ptr(this);
    if (m_disappearDuration > 0 && !m_isDisappearing)
    {
        m_isDisappearing = true;
        QTimer::singleShot(m_disappearDuration, this, [=]() {
            if (ptr == nullptr)
                return;

            m_opacityAni->setDuration(100);
            m_opacityAni->setStartValue(1);
            m_opacityAni->setEndValue(0);
            connect(m_opacityAni, &QPropertyAnimation::finished, [=]() { m_closeButton->clicked(); });
            m_opacityAni->start();
        });
    }
}

void FluShortInfoBar::setDisappearDuration(int disappearDuration)
{
    m_disappearDuration = disappearDuration;
}

QPushButton* FluShortInfoBar::getCloseButton()
{
    return m_closeButton;
}

void FluShortInfoBar::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluShortInfoBar::onThemeChanged()
{
    m_closeButton->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUtils::setQssByFileName("FluShortInfoBar.qss", this, FluThemeUtils::getUtils()->getTheme());
}
