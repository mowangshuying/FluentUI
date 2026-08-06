#include "FluSlider.h"

#include <QKeyEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QStyle>

FluSlider::FluSlider(QWidget* parent) : QSlider(parent)
{
    m_valueTooltip = new QLabel(nullptr, Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    m_valueTooltip->setObjectName("sliderValueTooltip");
    m_valueTooltip->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_valueTooltip->setAttribute(Qt::WA_StyledBackground, true);
    m_valueTooltip->setAttribute(Qt::WA_TranslucentBackground);

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
    m_valueTooltip = new QLabel(nullptr, Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    m_valueTooltip->setObjectName("sliderValueTooltip");
    m_valueTooltip->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_valueTooltip->setAttribute(Qt::WA_StyledBackground, true);
    m_valueTooltip->setAttribute(Qt::WA_TranslucentBackground);

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

FluSlider::~FluSlider()
{
    delete m_valueTooltip;
}

void FluSlider::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluSlider.qss", this, FluThemeUtils::getUtils()->getTheme());
    updateTooltipStyle();
    update();
}

void FluSlider::updateTooltipStyle()
{
    if (!m_valueTooltip)
        return;

    FluTheme theme = FluThemeUtils::getUtils()->getTheme();
    QString style;
    if (theme == FluTheme::AtomOneDark)
    {
        style = "QLabel#sliderValueTooltip { background-color: rgb(44, 48, 54); color: white; border: 1px solid rgb(71, 74, 79); border-bottom: 1px solid rgb(71, 74, 79); border-radius: 4px; padding: 4px 8px; }";
    }
    else if (FluThemeUtils::isLightTheme())
    {
        style = "QLabel#sliderValueTooltip { background-color: rgb(251, 251, 251); color: black; border: 1px solid rgb(229, 229, 229); border-bottom: 1px solid rgb(204, 204, 204); border-radius: 4px; padding: 4px 8px; }";
    }
    else
    {
        style = "QLabel#sliderValueTooltip { background-color: rgb(45, 45, 45); color: white; border: 1px solid rgb(53, 53, 53); border-bottom: 1px solid rgb(48, 48, 48); border-radius: 4px; padding: 4px 8px; }";
    }
    m_valueTooltip->setStyleSheet(style);
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
    if (enable)
    {
        if (orientation() == Qt::Horizontal)
            setMinimumHeight(qMax(minimumHeight(), 64));
        else
            setMinimumWidth(qMax(minimumWidth(), 96));
    }
    update();
}

bool FluSlider::isTickMarkEnabled() const
{
    return m_tickMarkEnabled;
}

void FluSlider::setTickMarkInterval(int interval)
{
    m_tickMarkInterval = qMax(1, interval);
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
    const qreal handleRadius = 8.0 * m_handleScale;

    // Compute knob center using the same qBound clamp as paintEvent
    qreal ratio = (qreal)(value() - min) / range;
    qreal knobCenterX, knobCenterY;
    if (orientation() == Qt::Horizontal)
    {
        qreal x = ratio * (width() - 1);
        x = qBound(handleRadius, x, (qreal)(width() - 1) - handleRadius);
        knobCenterX = x;
        knobCenterY = height() / 2.0;
    }
    else
    {
        qreal y = (1.0 - ratio) * (height() - 1);
        y = qBound(handleRadius, y, (qreal)(height() - 1) - handleRadius);
        knobCenterX = width() / 2.0;
        knobCenterY = y;
    }

    m_valueTooltip->setText(text);
    m_valueTooltip->adjustSize();

    QPoint globalCenter = mapToGlobal(QPoint(qRound(knobCenterX), qRound(knobCenterY)));
    QPoint tooltipPos;
    if (orientation() == Qt::Horizontal)
    {
        // Keep the tooltip 8px above the actual knob top and center it on the knob.
        tooltipPos.setX(globalCenter.x() - m_valueTooltip->width() / 2);
        tooltipPos.setY(globalCenter.y() - qRound(handleRadius) - 8 - m_valueTooltip->height());
    }
    else
    {
        // Keep vertical tooltip centered on the knob and to its right.
        tooltipPos.setX(globalCenter.x() + qRound(handleRadius) + 12);
        tooltipPos.setY(globalCenter.y() - m_valueTooltip->height() / 2);
    }

    m_valueTooltip->move(tooltipPos);
    m_valueTooltip->show();
}

void FluSlider::hideValueTooltip()
{
    if (m_valueTooltip)
        m_valueTooltip->hide();
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

    // Draw ruler-style tick marks (optional), aligned with the fixed handle travel range.
    if (m_tickMarkEnabled)
    {
        QColor tickColor = isLight ? QColor(105, 105, 105) : QColor(185, 185, 185);
        if (isAtomDark)
            tickColor = QColor(150, 156, 170);
        if (!isEnabled())
            tickColor = isLight ? QColor(180, 180, 180) : QColor(95, 95, 95);

        QPen tickPen(tickColor, 1.0);
        tickPen.setCapStyle(Qt::RoundCap);
        painter.setPen(tickPen);

        const int interval = qMax(1, m_tickMarkInterval);
        QFont tickFont = font();
        if (tickFont.pointSizeF() > 0)
            tickFont.setPointSizeF(qMax(7.0, tickFont.pointSizeF() - 1.0));
        painter.setFont(tickFont);
        QFontMetrics tickFm(tickFont);

        int maxLabelWidth = 0;
        for (int v = min; v <= max; v += interval)
            maxLabelWidth = qMax(maxLabelWidth, tickFm.horizontalAdvance(QString::number(v)));
        if ((max - min) % interval != 0)
            maxLabelWidth = qMax(maxLabelWidth, tickFm.horizontalAdvance(QString::number(max)));

        auto drawHorizontalTick = [&](int v) {
            qreal ratio = (qreal)(v - min) / range;
            const qreal travelStart = baseRadius;
            const qreal travelEnd = width() - 1 - baseRadius;
            int x = qRound(travelStart + ratio * (travelEnd - travelStart));

            const bool isEndpoint = (v == min || v == max);
            const int tickLen = isEndpoint ? 8 : 5;
            const int tickTop = qRound(height() / 2.0 + 8);
            painter.drawLine(x, tickTop, x, tickTop + tickLen);

            QString label = QString::number(v);
            int labelW = tickFm.horizontalAdvance(label);
            int labelX = qBound(0, x - labelW / 2, qMax(0, width() - labelW));
            int labelY = tickTop + tickLen + 3;
            labelY = qMin(labelY, qMax(0, height() - tickFm.height()));
            QRect labelRect(labelX, labelY, labelW, tickFm.height());
            painter.drawText(labelRect, Qt::AlignCenter, label);
        };

        auto drawVerticalTick = [&](int v) {
            qreal ratio = 1.0 - (qreal)(v - min) / range;
            const qreal travelStart = baseRadius;
            const qreal travelEnd = height() - 1 - baseRadius;
            int y = qRound(travelStart + ratio * (travelEnd - travelStart));

            const bool isEndpoint = (v == min || v == max);
            const int tickLen = isEndpoint ? 8 : 5;
            const int desiredTickLeft = qRound(width() / 2.0 + 8);
            const int tickLeftMax = width() - tickLen - 4 - maxLabelWidth;
            const int tickLeft = qBound(0, desiredTickLeft, qMax(0, tickLeftMax));
            painter.drawLine(tickLeft, y, tickLeft + tickLen, y);

            QString label = QString::number(v);
            int labelW = tickFm.horizontalAdvance(label);
            int labelX = tickLeft + tickLen + 4;
            int labelY = qBound(0, y - tickFm.height() / 2, qMax(0, height() - tickFm.height()));
            QRect labelRect(labelX, labelY, labelW, tickFm.height());
            painter.drawText(labelRect, Qt::AlignVCenter | Qt::AlignLeft, label);
        };

        if (orientation() == Qt::Horizontal)
        {
            int lastValue = min;
            for (int v = min; v <= max; v += interval)
            {
                drawHorizontalTick(v);
                lastValue = v;
            }
            if (lastValue != max)
                drawHorizontalTick(max);
        }
        else
        {
            int lastValue = min;
            for (int v = min; v <= max; v += interval)
            {
                drawVerticalTick(v);
                lastValue = v;
            }
            if (lastValue != max)
                drawVerticalTick(max);
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
