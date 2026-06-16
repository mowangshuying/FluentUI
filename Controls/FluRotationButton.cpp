#include "FluRotationButton.h"

FluRotationButton::FluRotationButton(QWidget* parent /*= nullptr*/) : QPushButton(parent)
{
    m_timer = new QTimer(this);
    m_timer->start();
    m_timer->setInterval(1000 / 60);
    m_bRotation = false;
    m_nAngle = 0;
    m_nReserveAngle = 0;

    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluRotationButton::FluRotationButton(FluAwesomeType awesomeType, QWidget* parent /*= nullptr*/) : FluRotationButton(parent)
{
    m_awesomeType = awesomeType;
    onThemeChanged();
}

void FluRotationButton::setAwesomeType(FluAwesomeType awesomeType)
{
    m_awesomeType = awesomeType;
}

void FluRotationButton::setRotation(bool b)
{
    m_bRotation = b;
}

void FluRotationButton::setReserveAngle(int nReserveAngle)
{
    m_nReserveAngle = nReserveAngle;
    m_timer->start();
}

void FluRotationButton::onTimeOut()
{
    if (m_nReserveAngle <= 0)
    {
        m_timer->stop();
        m_nReserveAngle = 0;
        return;
    }

    QTransform transform;
    transform.rotate(m_nAngle);

    // QPixmap pixmap = FluIconUtils::getFluentIconPixmap(m_awesomeType, m_penColor);
    QPixmap pixmap = FluIconUtils::getFluentIconPixmap(m_awesomeType, FluThemeUtils::getUtils()->getTheme());
    pixmap = pixmap.transformed(transform);
    QIcon icon(pixmap);
    setIcon(icon);

    m_nReserveAngle--;
    m_nAngle += 90;
}

void FluRotationButton::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Light));
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluRotationButton.qss", this);
    }
    else
    {
        setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Dark));
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluRotationButton.qss", this);
    }
    FluStyleSheetUitls::setQssByFileName("FluRotationButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}
