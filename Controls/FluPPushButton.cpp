#include "FluPPushButton.h"
#include <QStyle>

FluPPushButton::FluPPushButton(QWidget* parent /*= nullptr*/) : QPushButton(parent), m_mouseState(FluPPUtils::PPMouseState::Normal)
{
    setMouseTracking(true);
    installEventFilter(this);
    setFixedHeight(30);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=]() 
        { 
            onThemeChanged();
        });
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

QColor FluPPushButton::getBottomBorderColor()
{
    return m_bottomBorderColor;
}


void FluPPushButton::setBottomBorderColor(QColor color)
{
    m_bottomBorderColor = color;
    update();
}

QColor FluPPushButton::getTextColor()
{
    return m_textColor;
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
            FluPPUtils::setPPMouseState(this, FluPPUtils::PPMouseState::Hover);
            style()->polish(this);
            break;
        case QEvent::Leave:
            FluPPUtils::setPPMouseState(this, FluPPUtils::PPMouseState::Normal);
            style()->polish(this);
            break;
        case QEvent::MouseButtonPress:
            FluPPUtils::setPPMouseState(this, FluPPUtils::PPMouseState::Pressed);
            style()->polish(this);
            break;
        case QEvent::MouseButtonRelease:
            FluPPUtils::setPPMouseState(this, FluPPUtils::PPMouseState::Hover);
            style()->polish(this);
            break;
        default:
            break;
    }

    return bFilter;
}

void FluPPushButton::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluPPushButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}