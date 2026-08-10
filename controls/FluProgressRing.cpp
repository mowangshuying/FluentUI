#include "FluProgressRing.h"

FluProgressRing::FluProgressRing(QWidget* parent /*= nullptr*/)
    : FluWidget(parent), m_isTransparentTrack(true)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_curValue = 0;
    m_isWorking = false;
    m_isShowText = false;
    m_animValue = 0.0;
    m_workAngle = 0.0;
    m_progressColor = QColor(0, 90, 158);
    m_trackColor = QColor(211, 211, 211);
    m_textColor = QColor(26, 26, 26);
    setFixedSize(60, 60);

    // Determinate: smooth progress transition (WinUI3 spec ~200ms OutCubic).
    m_valueAnim = new QPropertyAnimation(this, "animValue", this);
    m_valueAnim->setDuration(200);
    m_valueAnim->setEasingCurve(QEasingCurve::OutCubic);

    // Indeterminate: a single arc segment continuously rotating around the circle.
    // A Linear 0->360 infinite loop; 360 wraps back to 0 (same angle) so it never jumps.
    m_workAngleAnim = new QPropertyAnimation(this, "workAngle", this);
    m_workAngleAnim->setDuration(1200);  // full rotation period
    m_workAngleAnim->setLoopCount(-1);
    m_workAngleAnim->setStartValue(0.0);
    m_workAngleAnim->setEndValue(360.0);
    m_workAngleAnim->setEasingCurve(QEasingCurve::Linear);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme) { onThemeChanged(); });
}

FluProgressRing::~FluProgressRing()
{
    if (m_workAngleAnim)
        m_workAngleAnim->stop();
    if (m_valueAnim)
        m_valueAnim->stop();
}

void FluProgressRing::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    const qreal minWH = qMin(width(), height());

    // Adaptive pen width: scale with ring size so small rings (25px) stay
    // coordinated and large rings (60px) don't look too thin.
    const qreal trunkW = qBound(3.0, minWH * 0.1, 6.0);

    QPen pen;
    pen.setWidthF(trunkW);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    // Track color (theme-aware via QSS qproperty-trackColor).
    pen.setColor(m_trackColor);
    if (m_isTransparentTrack)
        pen.setColor(Qt::transparent);

    painter.setPen(pen);
    QRectF outerC(trunkW / 2.0, trunkW / 2.0, minWH - trunkW, minWH - trunkW);
    painter.drawEllipse(outerC);

    // Progress arc color (theme-aware via QSS qproperty-progressColor).
    pen.setColor(m_progressColor);
    painter.setPen(pen);

    if (m_isWorking)
    {
        // Indeterminate: a ~90° arc segment rotating clockwise, no jump.
        // Negative start angle moves the arc clockwise as m_workAngle grows.
        painter.drawArc(outerC, -m_workAngle * 16.0, -360.0 * 16.0 * 0.25);
    }
    else
    {
        // Determinate: use the animated value so progress transitions smoothly.
        const int range = m_maxValue - m_minValue;
        const qreal ratio = (range > 0) ? qBound(0.0, (m_animValue - m_minValue) / range, 1.0) : 0.0;
        painter.drawArc(outerC, 90.0 * 16.0, -360.0 * 16.0 * ratio);
    }

    if (!m_isWorking && m_isShowText)
    {
        pen.setWidthF(1.0);
        pen.setColor(m_textColor);
        painter.setPen(pen);

        const int range = m_maxValue - m_minValue;
        const int percent = (range > 0) ? m_curValue * 100 / range : 0;
        painter.drawText(outerC, Qt::AlignCenter, QString::asprintf("%d%%", percent));
    }
}

void FluProgressRing::setMinMaxValue(int minValue, int maxValue)
{
    m_minValue = minValue;
    m_maxValue = maxValue;
}

QColor FluProgressRing::getProgressColor() const
{
    return m_progressColor;
}

void FluProgressRing::setProgressColor(const QColor& color)
{
    m_progressColor = color;
    update();
}

QColor FluProgressRing::getTrackColor() const
{
    return m_trackColor;
}

void FluProgressRing::setTrackColor(const QColor& color)
{
    m_trackColor = color;
    update();
}

QColor FluProgressRing::getTextColor() const
{
    return m_textColor;
}

void FluProgressRing::setTextColor(const QColor& color)
{
    m_textColor = color;
    update();
}

void FluProgressRing::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluProgressRing.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluProgressRing::setCurValue(int curValue)
{
    m_curValue = curValue;
    if (m_isWorking)
        return;  // don't animate while indeterminate

    m_valueAnim->stop();
    m_valueAnim->setStartValue(m_animValue);
    m_valueAnim->setEndValue(static_cast<double>(curValue));
    m_valueAnim->start();
}

int FluProgressRing::getCurValue()
{
    return m_curValue;
}

bool FluProgressRing::getWorking()
{
    return m_isWorking;
}

void FluProgressRing::setWorking(bool isWorking)
{
    if (m_isWorking == isWorking)
        return;
    m_isWorking = isWorking;

    if (isWorking)
    {
        m_valueAnim->stop();
        m_workAngleAnim->start();
    }
    else
    {
        m_workAngleAnim->stop();
        m_valueAnim->stop();
        m_animValue = static_cast<double>(m_curValue);  // sync to logical value
    }
    update();
}

void FluProgressRing::setShowText(bool isShowText)
{
    m_isShowText = isShowText;
    update();
}

bool FluProgressRing::getShowText()
{
    return m_isShowText;
}

bool FluProgressRing::getTransparentTrack()
{
    return m_isTransparentTrack;
}

void FluProgressRing::setTransparentTrack(bool isTransparentTrack)
{
    m_isTransparentTrack = isTransparentTrack;
    update();
}