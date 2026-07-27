#include "FluScaleButton.h"

FluScaleButton::FluScaleButton(FluAwesomeType awesomeType, QWidget* parent /*= nullptr*/) : QPushButton(parent), m_iconType(awesomeType)
{
    setFixedSize(30, 30);
    m_isPressed = false;

    m_currentPercentage = 1;
    scaleByPercentage(1);
    initTimer();

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluScaleButton::initTimer()
{
    m_timer = new QTimer(this);
    m_timer->setInterval(20);
    connect(m_timer, &QTimer::timeout, this, [=]() {
        if (m_isPressed)
        {
            m_currentPercentage -= 0.1;
            if (m_currentPercentage > 0)
            {
                scaleByPercentage(m_currentPercentage);
            }
            else
            {
                m_timer->stop();
            }
        }
        else
        {
            m_currentPercentage += 0.1;
            if (m_currentPercentage < 1)
            {
                scaleByPercentage(m_currentPercentage);
            }
            else
            {
                m_timer->stop();
            }
        }
    });
}

void FluScaleButton::scaleByPercentage(float scale)
{
    int wH = 18 + 6 * scale;
    setIconSize(QSize(wH, wH));
    QPixmap pixmap = FluIconUtils::getFluentIconPixmap(m_iconType, FluThemeUtils::getUtils()->getTheme());
    pixmap = pixmap.scaled(wH, wH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setIcon(QIcon(pixmap));
}

void FluScaleButton::mousePressEvent(QMouseEvent* e)
{
    if (m_isPressed == true)
        return;

    m_isPressed = true;
    m_timer->start();
}

void FluScaleButton::mouseReleaseEvent(QMouseEvent* e)
{
    m_isPressed = false;
    m_timer->stop();
    m_timer->start();
}

void FluScaleButton::onThemeChanged()
{
    scaleByPercentage(m_currentPercentage);
    FluStyleSheetUtils::setQssByFileName("FluScaleButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}
