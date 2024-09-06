#include "FluPPushButton.h"

FluPPushButton::FluPPushButton(QWidget* parent /*= nullptr*/) : QPushButton(parent), m_mouseState(FluMouseState::Normal)
{
    setMouseTracking(true);
    setFixedHeight(30);

    // updateColorNormal();
    updateColor();
    installEventFilter(this);

    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=]() { updateColor(); });
}

void FluPPushButton::updateColor()
{
    updateColorNormal();
    updateColorHover();
    updateColorPressed();
    update();
}

void FluPPushButton::updateColorNormal()
{
    if (m_mouseState != FluMouseState::Normal)
        return;

    if (FluThemeUtils::isLightTheme())
    {
        setBackgroundColor(QColor(251, 251, 251));
        setBorderColor(QColor(229, 229, 229));
        setBottomBorderColor(QColor(204, 204, 204));
        setTextColor(Qt::black);
        return;
    }

    if (FluThemeUtils::isDarkTheme())
    {
        setBackgroundColor(QColor(45, 45, 45));
        setBorderColor(QColor(53, 53, 53));
        setBottomBorderColor(QColor(48, 48, 48));
        setTextColor(Qt::white);
        return;
    }
}

void FluPPushButton::updateColorHover()
{
    if (m_mouseState != FluMouseState::Hover)
        return;

    if (FluThemeUtils::isLightTheme())
    {
        setBackgroundColor(QColor(246, 246, 246));
        setBorderColor(QColor(229, 229, 229));
        setBottomBorderColor(QColor(204, 204, 204));
        setTextColor(Qt::black);
        return;
    }

    if (FluThemeUtils::isDarkTheme())
    {
        setBackgroundColor(QColor(50, 50, 50));
        setBorderColor(QColor(53, 53, 53));
        setBottomBorderColor(QColor(48, 48, 48));
        setTextColor(Qt::white);
        return;
    }
}

void FluPPushButton::updateColorPressed()
{
    if (m_mouseState != FluMouseState::Pressed)
    {
        return;
    }

    if (FluThemeUtils::isLightTheme())
    {
        setBackgroundColor(QColor(245, 245, 245));
        setBorderColor(QColor(229, 229, 229));
        setBottomBorderColor(QColor(229, 229, 229));
        setTextColor(Qt::black);
        return;
    }

    if (FluThemeUtils::isDarkTheme())
    {
        setBackgroundColor(QColor(39, 39, 39));
        setBorderColor(QColor(53, 53, 53));
        setBottomBorderColor(QColor(39, 39, 39));
        setTextColor(Qt::white);
        return;
    }
}

QColor FluPPushButton::getBackgroundColor()
{
    return m_backgroundColor;
}

void FluPPushButton::setBackgroundColor(QColor color)
{
    m_backgroundColor = color;
    update();
}

QColor FluPPushButton::getBorderColor()
{
    return m_borderColor;
}

void FluPPushButton::setBorderColor(QColor color)
{
    m_borderColor = color;
    update();
}

void FluPPushButton::setBottomBorderColor(QColor color)
{
    m_bottomBorderColor = color;
    update();
}

QColor FluPPushButton::getTextColor()
{
    return m_textColor;
    update();
}

void FluPPushButton::setTextColor(QColor color)
{
    m_textColor = color;
    update();
}

void FluPPushButton::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(m_borderColor);
    painter.setPen(pen);
    painter.setBrush(QBrush(m_backgroundColor));
    QRect backgroundRect = rect();
    painter.drawRoundedRect(backgroundRect, 4, 4);

    pen.setWidth(1);
    pen.setColor(m_bottomBorderColor);
    painter.setPen(pen);
    painter.drawLine(QPoint(2, rect().height()), QPoint(rect().width() - 2, rect().height()));

    pen.setColor(m_textColor);
    painter.setPen(pen);
    painter.drawText(rect(), Qt::AlignCenter, text());
}

bool FluPPushButton::eventFilter(QObject* watched, QEvent* event)
{
    bool bFilter = QPushButton::eventFilter(watched, event);

    switch (event->type())
    {
        case QEvent::Enter:
            m_mouseState = FluMouseState::Hover;
            updateColor();
            break;
        case QEvent::Leave:
            m_mouseState = FluMouseState::Normal;
            updateColor();
            break;
        case QEvent::MouseButtonPress:
            m_mouseState = FluMouseState::Pressed;
            updateColor();
            break;
        case QEvent::MouseButtonRelease:
            m_mouseState = FluMouseState::Hover;
            updateColor();
            break;
        default:
            break;
    }

    return bFilter;
}
