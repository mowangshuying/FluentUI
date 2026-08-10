#include "FluShortInfoBar.h"
#include "FluInfoBarMgr.h"
#include <QPointer>
#include <QTimer>

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

    m_opacity = 1.0;
    m_isDisappearing = false;

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

    m_opacityAni = new QPropertyAnimation(this, "opacity", this);
    connect(m_opacityAni, &QPropertyAnimation::finished, this, [this]() {
        if (m_isDisappearing)
        {
            m_isDisappearing = false;
            m_closeButton->clicked();
        }
    });

    connect(m_closeButton, &QPushButton::clicked, [=]() {
        FluInfoBarMgr::getInstance()->removeInfoBar(this);
        close();
        deleteLater();
    });

    updateInfoBarTypeProperty(infobarType);
    m_disappearDuration = -1;

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
            m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Warning, QColor(239, 239, 239), 18, 18));
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

            m_opacityAni->stop();
            m_opacityAni->setDuration(250);
            m_opacityAni->setEasingCurve(QEasingCurve::InOutCubic);
            m_opacityAni->setStartValue(m_opacity);
            m_opacityAni->setEndValue(0.0);
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

double FluShortInfoBar::getOpacity() const
{
    return m_opacity;
}

void FluShortInfoBar::setOpacity(double opacity)
{
    if (!qFuzzyCompare(m_opacity + 1, opacity + 1))
    {
        m_opacity = opacity;
        update();
    }
}

void FluShortInfoBar::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    showFadeIn();
}

void FluShortInfoBar::showFadeIn()
{
    m_opacity = 0.0;
    update();
    m_opacityAni->stop();
    m_opacityAni->setDuration(200);
    m_opacityAni->setEasingCurve(QEasingCurve::OutCubic);
    m_opacityAni->setStartValue(0.0);
    m_opacityAni->setEndValue(1.0);
    m_opacityAni->start();
}

void FluShortInfoBar::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    painter.setOpacity(m_opacity);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluShortInfoBar::onThemeChanged()
{
    m_closeButton->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUtils::setQssByFileName("FluShortInfoBar.qss", this, FluThemeUtils::getUtils()->getTheme());
}