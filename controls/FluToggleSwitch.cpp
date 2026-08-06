#include "FluToggleSwitch.h"
#include <QPainterPath>
#include <QMouseEvent>
#include <QKeyEvent>

static QColor interpolateColor(const QColor& from, const QColor& to, qreal t)
{
    t = qBound(0.0, t, 1.0);
    return QColor(
        static_cast<int>(from.red() + (to.red() - from.red()) * t),
        static_cast<int>(from.green() + (to.green() - from.green()) * t),
        static_cast<int>(from.blue() + (to.blue() - from.blue()) * t));
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
    const qreal offX = 11.0;
    const qreal onX = 31.0;
    startKnobAnimation(m_checked ? onX : offX);

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

    // Compute text metrics
    QFontMetrics fm(font());
    bool hasText = !m_text.isEmpty();
    int textWidth = hasText ? fm.horizontalAdvance(m_text) : 0;
    int textHeight = fm.height();

    // Track dimensions
    const int tw = kTrackWidth;
    const int th = kTrackHeight;
    const int trackY = (height() - th) / 2;

    // Track rect: positioned left or right of text
    QRectF trackRect;
    QRect textRect;
    if (m_textPosition == TextPosition::Left && hasText)
    {
        textRect = QRect(0, (height() - textHeight) / 2, textWidth, textHeight);
        trackRect = QRectF(textWidth + kTextGap, trackY, tw, th);
    }
    else
    {
        trackRect = QRectF(0, trackY, tw, th);
        if (hasText)
            textRect = QRect(tw + kTextGap, (height() - textHeight) / 2, textWidth, textHeight);
    }

    // Interpolate track fill color based on knobX position (off -> on)
    const qreal t = (m_knobX - 11.0) / (31.0 - 11.0);
    QColor trackFill = interpolateColor(m_fillColor, m_fillColorOn, t);
    QColor trackBorder = m_checked ? m_fillColorOn : m_borderColor;

    // Draw track (rounded rect)
    QPainterPath trackPath;
    trackPath.addRoundedRect(trackRect, th / 2.0, th / 2.0);

    // Border (1px)
    QPen borderPen(trackBorder, 1.0);
    painter.setPen(borderPen);
    painter.setBrush(trackFill);
    painter.drawRoundedRect(trackRect, th / 2.0, th / 2.0);

    // Draw knob
    const qreal knobRadius = m_isHovered ? kKnobRadiusHover : kKnobRadius;
    const qreal knobCenterY = trackRect.center().y();
    const qreal knobCenterX = trackRect.left() + m_knobX;

    painter.setPen(Qt::NoPen);
    painter.setBrush(m_knobColor);
    painter.drawEllipse(QPointF(knobCenterX, knobCenterY), knobRadius, knobRadius);

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
    int textWidth = m_text.isEmpty() ? 0 : fm.horizontalAdvance(m_text);
    int w = kTrackWidth;
    int h = kMinHeight;

    if (textWidth > 0)
    {
        w += kTextGap + textWidth;
        h = qMax(h, fm.height() + 2);
    }

    return QSize(w, h);
}

QSize FluToggleSwitch::minimumSizeHint() const
{
    return QSize(kTrackWidth, kMinHeight);
}

void FluToggleSwitch::updateSize()
{
    setFixedSize(sizeHint());
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
