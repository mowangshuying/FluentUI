#include "FluSlider.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QToolTip>

FluSlider::FluSlider(QWidget* parent) : QSlider(parent)
{
    // Initialize handle scale animation
    m_scaleAnim = new QPropertyAnimation(this, "handleScale", this);
    m_scaleAnim->setDuration(150);
    m_scaleAnim->setEasingCurve(QEasingCurve::OutCubic);

    // Initialize value jump animation
    m_valueAnim = new QPropertyAnimation(this, "animValue", this);
    m_valueAnim->setDuration(200);
    m_valueAnim->setEasingCurve(QEasingCurve::OutCubic);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluSlider::FluSlider(Qt::Orientation orientation, QWidget* parent) : QSlider(orientation, parent)
{
    // Initialize handle scale animation
    m_scaleAnim = new QPropertyAnimation(this, "handleScale", this);
    m_scaleAnim->setDuration(150);
    m_scaleAnim->setEasingCurve(QEasingCurve::OutCubic);

    // Initialize value jump animation
    m_valueAnim = new QPropertyAnimation(this, "animValue", this);
    m_valueAnim->setDuration(200);
    m_valueAnim->setEasingCurve(QEasingCurve::OutCubic);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluSlider::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluSlider.qss", this, FluThemeUtils::getUtils()->getTheme());
    update();
}

// --- Handle scale property ---

qreal FluSlider::handleScale() const
{
    return m_handleScale;
}

void FluSlider::setHandleScale(qreal scale)
{
    m_handleScale = scale;
    update();
}

void FluSlider::animateHandleTo(qreal target)
{
    if (!m_scaleAnim)
        return;
    m_scaleAnim->stop();
    m_scaleAnim->setStartValue(m_handleScale);
    m_scaleAnim->setEndValue(target);
    m_scaleAnim->setDuration(150);
    m_scaleAnim->setEasingCurve(QEasingCurve::OutCubic);
    m_scaleAnim->start();
}

// --- Read-only API ---

void FluSlider::setReadOnly(bool readOnly)
{
    m_readOnly = readOnly;
    update();
}

bool FluSlider::isReadOnly() const
{
    return m_readOnly;
}

// --- Value animation property ---

int FluSlider::animValue() const
{
    return m_animValue;
}

void FluSlider::setAnimValue(int v)
{
    m_animValue = v;
    QSlider::setValue(v);
    update();
}

void FluSlider::animateToValue(int target)
{
    if (m_readOnly)
        return;
    m_animatingValue = true;
    m_valueAnim->stop();
    m_valueAnim->setStartValue(value());
    m_valueAnim->setEndValue(target);
    m_valueAnim->start();
    connect(m_valueAnim, &QPropertyAnimation::finished, this, [=]() { m_animatingValue = false; }, Qt::SingleShotConnection);
}

// --- Tick mark API ---

void FluSlider::setTickMarkEnabled(bool enable)
{
    m_tickMarkEnabled = enable;
    update();
}

bool FluSlider::isTickMarkEnabled() const
{
    return m_tickMarkEnabled;
}

void FluSlider::setTickMarkInterval(int interval)
{
    m_tickMarkInterval = interval;
    update();
}

int FluSlider::getTickMarkInterval() const
{
    return m_tickMarkInterval;
}

// --- Tooltip API ---

void FluSlider::setTooltipEnabled(bool enable)
{
    m_tooltipEnabled = enable;
    if (!enable)
        hideValueTooltip();
}

bool FluSlider::isTooltipEnabled() const
{
    return m_tooltipEnabled;
}

void FluSlider::showValueTooltip()
{
    // Only refresh tooltip when value actually changes
    if (m_lastValue == value())
        return;
    m_lastValue = value();

    int min = minimum();
    int max = maximum();
    int range = max - min;
    if (range <= 0)
        return;

    const QString text = QString::number(value());
    const qreal baseRadius = 8.0;

    // Compute knob center using the same qBound clamp as paintEvent
    qreal ratio = (qreal)(value() - min) / range;
    qreal knobCenterX, knobCenterY;
    if (orientation() == Qt::Horizontal)
    {
        qreal x = ratio * (width() - 1);
        x = qBound(baseRadius, x, (qreal)(width() - 1) - baseRadius);
        knobCenterX = x;
        knobCenterY = height() / 2.0;
    }
    else
    {
        qreal y = (1.0 - ratio) * (height() - 1);
        y = qBound(baseRadius, y, (qreal)(height() - 1) - baseRadius);
        knobCenterX = width() / 2.0;
        knobCenterY = y;
    }

    QPoint globalPos;
    if (orientation() == Qt::Horizontal)
    {
        // Compute tooltip size from its font to allow precise placement
        QFontMetrics fm(QToolTip::font());
        QSize tipSize = fm.size(Qt::TextSingleLine, text);

        // Center tooltip horizontally on knob midline, place 8px above knob top edge
        int tipX = (int)(knobCenterX - tipSize.width() / 2.0);
        int tipY = (int)(knobCenterY - baseRadius - 8 - tipSize.height());
        globalPos = mapToGlobal(QPoint(tipX, tipY));
    }
    else
    {
        // Show tooltip to the right of the knob
        globalPos = mapToGlobal(QPoint((int)(knobCenterX + baseRadius + 12), (int)knobCenterY));
    }

    QToolTip::showText(globalPos, text, this);
}

void FluSlider::hideValueTooltip()
{
    QToolTip::hideText();
    m_lastValue = -1;
}

// --- Input events ---

void FluSlider::mousePressEvent(QMouseEvent* event)
{
    if (m_readOnly)
    {
        event->ignore();
        return;
    }
    if (event->button() == Qt::LeftButton && isEnabled())
    {
        m_pressMousePos = event->pos();
        m_pressValue = value();
        m_isClickOnly = true;
        m_pressed = true;
        animateHandleTo(0.9);

        // Show tooltip immediately on press for feedback before value change
        if (m_tooltipEnabled)
        {
            m_lastValue = -1;
            showValueTooltip();
        }
        event->accept();
        return;
    }
    QSlider::mousePressEvent(event);
}

void FluSlider::mouseMoveEvent(QMouseEvent* event)
{
    if (m_readOnly || !m_pressed)
    {
        event->ignore();
        return;
    }

    // Transition from click to drag when movement exceeds threshold
    if (m_isClickOnly)
    {
        QPoint delta = event->pos() - m_pressMousePos;
        if (delta.manhattanLength() > kClickThreshold)
        {
            m_isClickOnly = false;
            m_dragging = true;
        }
    }

    if (m_dragging)
    {
        // Direct setValue during drag — no animation, maximally responsive
        if (orientation() == Qt::Horizontal)
            setValue(minimum() + (event->pos().x() / (qreal)width()) * (maximum() - minimum()));
        else
            setValue(minimum() + (1.0 - event->pos().y() / (qreal)height()) * (maximum() - minimum()));

        if (m_tooltipEnabled)
            showValueTooltip();
    }

    event->accept();
}

void FluSlider::mouseReleaseEvent(QMouseEvent* event)
{
    if (m_readOnly)
    {
        event->ignore();
        return;
    }

    bool wasClickOnly = m_isClickOnly && m_pressed;
    m_dragging = false;
    m_pressed = false;
    m_isClickOnly = false;

    hideValueTooltip();
    animateHandleTo(m_hovered ? 1.2 : 1.0);

    // Pure click (no drag): animate to the click target value
    if (wasClickOnly && isEnabled())
    {
        int target;
        if (orientation() == Qt::Horizontal)
            target = minimum() + (m_pressMousePos.x() / (qreal)width()) * (maximum() - minimum());
        else
            target = minimum() + (1.0 - m_pressMousePos.y() / (qreal)height()) * (maximum() - minimum());
        animateToValue(target);
    }

    QSlider::mouseReleaseEvent(event);
}

void FluSlider::keyPressEvent(QKeyEvent* event)
{
    if (m_readOnly)
    {
        event->ignore();
        return;
    }
    QSlider::keyPressEvent(event);
    // Show tooltip on keyboard adjustment
    if (m_tooltipEnabled)
        showValueTooltip();
    // Auto-hide tooltip after 1 second if not dragging
    QTimer::singleShot(1000, this, [=]() {
        if (!m_dragging)
            hideValueTooltip();
    });
}

void FluSlider::enterEvent(QEnterEvent* event)
{
    QSlider::enterEvent(event);
    m_hovered = true;
    if (!m_pressed)
        animateHandleTo(1.2);
}

void FluSlider::leaveEvent(QEvent* event)
{
    m_hovered = false;
    if (!m_pressed)
        animateHandleTo(1.0);
    if (!m_dragging)
        hideValueTooltip();
    QSlider::leaveEvent(event);
}

// --- Custom painting ---

void FluSlider::paintEvent(QPaintEvent* event)
{
    // Let QSlider draw the groove/sub-page/add-page via QSS
    QSlider::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    int min = minimum();
    int max = maximum();
    int range = max - min;
    if (range <= 0)
        return;

    // Determine theme-aware colors
    bool isLight = FluThemeUtils::isLightTheme();
    bool isAtomDark = (FluThemeUtils::getUtils()->getTheme() == FluTheme::AtomOneDark);

    // Accent color for the handle fill
    QColor accentColor;
    if (isAtomDark)
        accentColor = QColor(82, 139, 255);
    else if (isLight)
        accentColor = QColor(0, 90, 158);
    else
        accentColor = QColor(118, 185, 237);

    // Border color for the handle ring
    QColor borderColor;
    if (isAtomDark)
        borderColor = QColor(44, 48, 54);
    else if (isLight)
        borderColor = QColor(255, 255, 255);
    else
        borderColor = QColor(69, 69, 69);

    // Disabled override
    if (!isEnabled())
    {
        if (isAtomDark)
        {
            accentColor = QColor(70, 73, 78);
            borderColor = QColor(38, 42, 48);
        }
        else if (isLight)
        {
            accentColor = QColor(128, 128, 128);
            borderColor = QColor(204, 204, 204);
        }
        else
        {
            accentColor = QColor(80, 80, 80);
            borderColor = QColor(50, 50, 50);
        }
    }

    // Handle radius scaled by m_handleScale (WinUI 3 style)
    const qreal baseRadius = 8.0;
    qreal outerRadius = baseRadius * m_handleScale;
    qreal innerRadius = outerRadius - 3.0;

    // Draw tick marks (optional), positioned just outside the track area
    if (m_tickMarkEnabled)
    {
        // Match track gray tones per theme for visual cohesion
        QColor tickColor = isLight ? QColor(134, 134, 134) : QColor(154, 154, 154);
        if (isAtomDark)
            tickColor = QColor(154, 154, 154);
        if (!isEnabled())
            tickColor = isLight ? QColor(200, 200, 200) : QColor(60, 60, 60);

        painter.setPen(QPen(tickColor, 1.5));
        if (orientation() == Qt::Horizontal)
        {
            // Ticks placed below the track (track is centered vertically)
            int tickTop = height() / 2 + 12;
            for (int v = min; v <= max; v += m_tickMarkInterval)
            {
                qreal ratio = (qreal)(v - min) / range;
                int x = (int)(ratio * (width() - 1));
                x = qBound((int)outerRadius, x, (int)(width() - 1 - outerRadius));
                painter.drawLine(x, tickTop, x, tickTop + 14);
            }
        }
        else
        {
            // Ticks placed to the right of the track (track is centered horizontally)
            int tickLeft = width() / 2 + 12;
            for (int v = min; v <= max; v += m_tickMarkInterval)
            {
                qreal ratio = 1.0 - (qreal)(v - min) / range;
                int y = (int)(ratio * (height() - 1));
                y = qBound((int)outerRadius, y, (int)(height() - 1 - outerRadius));
                painter.drawLine(tickLeft, y, tickLeft + 14, y);
            }
        }
    }

    // Compute handle center, clamped so the handle stays fully inside the widget at extremes
    qreal ratio = (qreal)(value() - min) / range;
    QPointF center;
    if (orientation() == Qt::Horizontal)
    {
        qreal x = ratio * (width() - 1);
        x = qBound(outerRadius, x, width() - 1 - outerRadius);
        center = QPointF(x, height() / 2.0);
    }
    else
    {
        qreal y = (1.0 - ratio) * (height() - 1);
        y = qBound(outerRadius, y, height() - 1 - outerRadius);
        center = QPointF(width() / 2.0, y);
    }

    // Draw subtle shadow
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 30));
    painter.drawEllipse(center + QPointF(0, 1), outerRadius + 1, outerRadius + 1);

    // Draw outer border ring
    painter.setPen(Qt::NoPen);
    painter.setBrush(borderColor);
    painter.drawEllipse(center, outerRadius, outerRadius);

    // Draw accent fill (inner circle)
    painter.setBrush(accentColor);
    painter.drawEllipse(center, innerRadius, innerRadius);
}
