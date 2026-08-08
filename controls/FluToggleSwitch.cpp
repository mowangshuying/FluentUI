#include "FluToggleSwitch.h"
#include <QPainterPath>
#include <QMouseEvent>
#include <QKeyEvent>
#include <cmath>

static QColor interpolateColor(const QColor& from, const QColor& to, qreal t)
{
    t = qBound(0.0, t, 1.0);
    return QColor(static_cast<int>(from.red() + (to.red() - from.red()) * t), static_cast<int>(from.green() + (to.green() - from.green()) * t), static_cast<int>(from.blue() + (to.blue() - from.blue()) * t));
}

FluToggleSwitch::FluToggleSwitch(QWidget* parent) : FluWidget(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setAttribute(Qt::WA_Hover);
    setFocusPolicy(Qt::StrongFocus);

    m_knobAnimation = new QPropertyAnimation(this, "knobX", this);
    m_knobAnimation->setDuration(150);
    m_knobAnimation->setEasingCurve(QEasingCurve::OutCubic);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme) { onThemeChanged(); });

    updateMetrics();
    updateSize();
}

FluToggleSwitch::FluToggleSwitch(const QString& text, QWidget* parent) : FluToggleSwitch(parent)
{
    setText(text);
}

bool FluToggleSwitch::isChecked() const
{
    return m_checked;
}

void FluToggleSwitch::setChecked(bool checked)
{
    if (m_checked == checked)
        return;

    m_checked = checked;

    // Auto-switch display text based on state (unless emptyText is set)
    if (!m_emptyText && m_text.isEmpty())
    {
        m_text = m_checked ? m_onText : m_offText;
    }
    else if (!m_emptyText && (m_text == m_onText || m_text == m_offText))
    {
        m_text = m_checked ? m_onText : m_offText;
    }

    // Animate knob
    startKnobAnimation(m_checked ? m_actualKnobOnX : m_actualKnobOffX);

    emit checkedChanged(m_checked);
    emit toggled(m_checked);

    updateSize();
    update();
}

void FluToggleSwitch::toggle()
{
    setChecked(!m_checked);
}

QString FluToggleSwitch::getText() const
{
    return m_text;
}

void FluToggleSwitch::setText(const QString& text)
{
    if (m_text == text)
        return;
    m_text = text;
    updateSize();
    update();
}

QString FluToggleSwitch::getOnText() const
{
    return m_onText;
}

void FluToggleSwitch::setOnText(const QString& text)
{
    if (m_onText == text)
        return;
    m_onText = text;
    if (m_checked && !m_emptyText)
    {
        m_text = m_onText;
        updateSize();
    }
    update();
}

QString FluToggleSwitch::getOffText() const
{
    return m_offText;
}

void FluToggleSwitch::setOffText(const QString& text)
{
    if (m_offText == text)
        return;
    m_offText = text;
    if (!m_checked && !m_emptyText)
    {
        m_text = m_offText;
        updateSize();
    }
    update();
}

void FluToggleSwitch::setOnOffText(const QString& onText, const QString& offText)
{
    setOnText(onText);
    setOffText(offText);
    m_emptyText = false;
    m_text = m_checked ? m_onText : m_offText;
    updateSize();
    update();
}

bool FluToggleSwitch::isEmptyText() const
{
    return m_emptyText;
}

void FluToggleSwitch::setEmptyText(bool empty)
{
    if (m_emptyText == empty)
        return;
    m_emptyText = empty;
    if (m_emptyText)
        m_text.clear();
    else
        m_text = m_checked ? m_onText : m_offText;
    updateSize();
    update();
}

TextPosition FluToggleSwitch::getTextPosition() const
{
    return m_textPosition;
}

void FluToggleSwitch::setTextPosition(TextPosition pos)
{
    if (m_textPosition == pos)
        return;
    m_textPosition = pos;
    updateSize();
    update();
}

QColor FluToggleSwitch::getBorderColor() const
{
    return m_borderColor;
}

void FluToggleSwitch::setBorderColor(QColor color)
{
    m_borderColor = color;
    update();
}

QColor FluToggleSwitch::getFillColor() const
{
    return m_fillColor;
}

void FluToggleSwitch::setFillColor(QColor color)
{
    m_fillColor = color;
    update();
}

QColor FluToggleSwitch::getFillColorOn() const
{
    return m_fillColorOn;
}

void FluToggleSwitch::setFillColorOn(QColor color)
{
    m_fillColorOn = color;
    update();
}

QColor FluToggleSwitch::getKnobColor() const
{
    return m_knobColor;
}

void FluToggleSwitch::setKnobColor(QColor color)
{
    m_knobColor = color;
    update();
}

QColor FluToggleSwitch::getTextColor() const
{
    return m_textColor;
}

void FluToggleSwitch::setTextColor(QColor color)
{
    m_textColor = color;
    update();
}

qreal FluToggleSwitch::getKnobX() const
{
    return m_knobX;
}

void FluToggleSwitch::setKnobX(qreal x)
{
    if (qFuzzyCompare(m_knobX, x))
        return;
    m_knobX = x;
    update();
}

void FluToggleSwitch::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluToggleSwitch.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluToggleSwitch::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    if (!isEnabled())
        painter.setOpacity(0.4);

    // Text metrics: Small size omits text for legibility
    QFontMetrics fm(font());
    bool hasText = !m_text.isEmpty() && m_size != SwitchSize::Small;
    int textWidth = hasText ? fm.horizontalAdvance(m_text) : 0;
    int textHeight = fm.height();

    // Actual track dimensions (scaled by current size)
    const qreal tw = m_actualTrackWidth;
    const qreal th = m_actualTrackHeight;
    const int trackY = (height() - qRound(th)) / 2;

    // Border pen width: thinner for Small size
    const qreal pw = (m_size == SwitchSize::Small) ? 0.5 : 0.7;

    // Track rect: positioned left or right of text, inset by pw/2 for pixel-aligned border
    QRectF trackRect;
    QRect textRect;
    if (m_textPosition == TextPosition::Left && hasText)
    {
        textRect = QRect(0, (height() - textHeight) / 2, textWidth, textHeight);
        trackRect = QRectF(textWidth + pw / 2 + kTextGap * scaleFactor(), trackY + pw / 2, tw - pw, th - pw);
    }
    else
    {
        trackRect = QRectF(pw / 2, trackY + pw / 2, tw - pw, th - pw);
        if (hasText)
            textRect = QRect(qRound(tw) + qRound(kTextGap * scaleFactor()), (height() - textHeight) / 2, textWidth, textHeight);
    }

    // Interpolate track fill color based on knobX position (off -> on)
    const qreal t = (m_actualKnobOnX != m_actualKnobOffX) ? (m_knobX - m_actualKnobOffX) / (m_actualKnobOnX - m_actualKnobOffX) : 0.0;
    QColor trackFill = interpolateColor(m_fillColor, m_fillColorOn, t);
    QColor trackBorder = m_checked ? m_fillColorOn : m_borderColor;

    // Draw track (rounded rect)
    QPen borderPen(trackBorder, pw);
    painter.setPen(borderPen);
    painter.setBrush(trackFill);
    painter.drawRoundedRect(trackRect, th / 2.0, th / 2.0);

    // Draw knob: hover radius steps up by 1px (integer step) and rounds to keep the circle crisp
    const qreal normalRadius = m_knobRadius;
    const qreal displayKnobRadius = m_isHovered ? std::ceil(normalRadius + 1.0) : normalRadius;
    const qreal knobCenterY = std::round(trackY + th * 0.5);  // Integer-aligned for crisp circle
    // Keep the knob inside the track even when it grows on hover
    const qreal knobCenterX = static_cast<qreal>(qRound(qBound(trackRect.left() + displayKnobRadius, trackRect.left() + m_knobX, trackRect.right() - displayKnobRadius)));

    // Knob drop shadow for boundary clarity (WinUI 3 style, scaled)
    const QColor shadowColor(0, 0, 0, 40);
    const qreal shadowOffset = 0.5 * scaleFactor();
    const qreal shadowRadius = displayKnobRadius + 0.8 * scaleFactor();
    painter.setPen(Qt::NoPen);
    painter.setBrush(shadowColor);
    painter.drawEllipse(QPointF(knobCenterX, knobCenterY + shadowOffset), shadowRadius, shadowRadius);

    // Knob body with 0.5px subtle border
    QColor knobBorderColor = m_knobColor.darker(115);
    QPen knobBorderPen(knobBorderColor, 0.5);
    painter.setPen(knobBorderPen);
    painter.setBrush(m_knobColor);
    painter.drawEllipse(QPointF(knobCenterX, knobCenterY), displayKnobRadius, displayKnobRadius);

    // Draw text
    if (hasText)
    {
        painter.setPen(m_textColor);
        painter.drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, m_text);
    }
}

void FluToggleSwitch::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && isEnabled())
    {
        m_isPressed = true;
    }
    FluWidget::mousePressEvent(event);
}

void FluToggleSwitch::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_isPressed && isEnabled())
    {
        m_isPressed = false;
        toggle();
    }
    FluWidget::mouseReleaseEvent(event);
}

void FluToggleSwitch::enterEvent(QEnterEvent* event)
{
    m_isHovered = true;
    update();
    FluWidget::enterEvent(event);
}

void FluToggleSwitch::leaveEvent(QEvent* event)
{
    m_isHovered = false;
    m_isPressed = false;
    update();
    FluWidget::leaveEvent(event);
}

void FluToggleSwitch::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space || event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        if (isEnabled())
            toggle();
    }
    else
    {
        FluWidget::keyPressEvent(event);
    }
}

QSize FluToggleSwitch::sizeHint() const
{
    QFontMetrics fm(font());
    bool showText = !m_text.isEmpty() && m_size != SwitchSize::Small;
    int textWidth = showText ? fm.horizontalAdvance(m_text) : 0;
    int w = qRound(m_actualTrackWidth);
    int h = qMax(qRound(m_actualTrackHeight), kMinHeight);

    if (showText)
    {
        w += qRound(kTextGap * scaleFactor()) + textWidth;
        h = qMax(h, fm.height() + 2);
    }

    return QSize(w, h);
}

QSize FluToggleSwitch::minimumSizeHint() const
{
    return QSize(qRound(m_actualTrackWidth), qMax(qRound(m_actualTrackHeight), kMinHeight));
}

void FluToggleSwitch::updateSize()
{
    setFixedSize(sizeHint());
}

qreal FluToggleSwitch::scaleFactor() const
{
    switch (m_size)
    {
        case SwitchSize::Medium:
            return 0.8;
        case SwitchSize::Small:
            return 0.6;
        default:
            return 1.0;
    }
}

qreal FluToggleSwitch::scaleDim(int baseDim) const
{
    return baseDim * scaleFactor();
}

void FluToggleSwitch::updateMetrics()
{
    qreal f = scaleFactor();
    m_actualTrackWidth = kTrackWidth * f;
    m_actualTrackHeight = kTrackHeight * f;
    m_knobRadius = kKnobRadius * f;
    m_actualKnobOffX = m_knobRadius;
    m_actualKnobOnX = m_actualTrackWidth - m_knobRadius;
}

SwitchSize FluToggleSwitch::getSize() const
{
    return m_size;
}

void FluToggleSwitch::setSize(SwitchSize size)
{
    if (m_size == size)
        return;

    m_size = size;
    updateMetrics();

    // Stop any running animation and re-position knob to match new size
    if (m_knobAnimation)
        m_knobAnimation->stop();

    if (m_checked)
        m_knobX = m_actualKnobOnX;
    else
        m_knobX = m_actualKnobOffX;

    updateSize();
    update();
}

void FluToggleSwitch::startKnobAnimation(qreal targetX)
{
    if (!m_knobAnimation)
        return;

    m_knobAnimation->stop();
    m_knobAnimation->setStartValue(m_knobX);
    m_knobAnimation->setEndValue(targetX);
    m_knobAnimation->start();
}

int FluToggleSwitch::getTrackWidth() const
{
    return kTrackWidth;
}

int FluToggleSwitch::getTrackHeight() const
{
    return kTrackHeight;
}
