#include "FluProgressBar.h"

#include <QtMath>

FluProgressBar::FluProgressBar(QWidget* parent /*= nullptr*/) : QProgressBar(parent)
{
    setTextVisible(false);
    setFixedHeight(3);

    // Determinate: smooth value transition animation (WinUI3 spec: 167ms)
    m_valueAnim = new QPropertyAnimation(this, "animProgress", this);
    m_valueAnim->setDuration(167);
    m_valueAnim->setEasingCurve(QEasingCurve::OutCubic);

    // Fade animation for state transition (determinate <-> indeterminate)
    m_fadeAnim = new QPropertyAnimation(this, "determinateOpacity", this);
    m_fadeAnim->setDuration(167);
    m_fadeAnim->setEasingCurve(QEasingCurve::Linear);

    // Indeterminate: dual chunk staggered sliding timer (~60 fps)
    m_indetTimer = new QTimer(this);
    m_indetTimer->setInterval(16);

    // WinUI3 indeterminate: dual chunk, 2.0s cycle, spline 0.4,0.0,0.6,1.0
    // 2.0s / 60fps = 120 frames per cycle
    connect(m_indetTimer, &QTimer::timeout, this, [this]() {
        if (!m_isWorking)
            return;

        m_animCycle++;
        if (m_animCycle >= 120)  // 2.0s at 60fps (16ms * 120 = 1920ms)
            m_animCycle = 0;

        double t = m_animCycle / 120.0;  // [0, 1] over 2.0s

        // WinUI3 spline approximation: 0.4,0.0,0.6,1.0
        auto splineEase = [](double x) -> double {
            return x < 0.5 ? 4.0 * x * x * x : 1.0 - qPow(-2.0 * x + 2.0, 3.0) / 2.0;
        };

        // Chunk 1: 0.0s - 1.5s (75% of cycle)
        double t1 = qBound(0.0, t / 0.75, 1.0);
        m_chunk1Pos = -0.4 + splineEase(t1) * 1.4;  // from -40% to 100%
        if (t > 0.75)
            m_chunk1Pos = -0.4;  // hide after reaching end

        // Chunk 2: delayed start at 0.75s (37.5% of cycle)
        double t2 = qBound(0.0, (t - 0.375) / 0.625, 1.0);
        m_chunk2Pos = (t >= 0.375) ? (-0.4 + splineEase(t2) * 1.4) : -0.4;

        update();
    });

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [this](FluTheme) { onThemeChanged(); });
}

FluProgressBar::~FluProgressBar()
{
    if (m_indetTimer)
        m_indetTimer->stop();
}

bool FluProgressBar::isWorking() const
{
    return m_isWorking;
}

void FluProgressBar::setWorking(bool working)
{
    if (m_isWorking == working)
        return;
    m_isWorking = working;

    m_fadeAnim->stop();
    if (working)
    {
        m_chunk1Pos = 0.0;
        m_chunk2Pos = 0.0;
        m_animCycle = 0;
        m_indetTimer->start();

        // Fade out determinate, fade in indeterminate (from current opacity)
        m_fadeAnim->setStartValue(m_determinateOpacity);
        m_fadeAnim->setEndValue(0.0);
        m_fadeAnim->start();
    }
    else
    {
        m_indetTimer->stop();
        int range = maximum() - minimum();
        m_animProgress = (range > 0) ? static_cast<double>(value() - minimum()) / static_cast<double>(range) : 0.0;

        // Fade in determinate, fade out indeterminate (from current opacity)
        m_fadeAnim->setStartValue(m_determinateOpacity);
        m_fadeAnim->setEndValue(1.0);
        m_fadeAnim->start();
    }
    update();
}

void FluProgressBar::setValue(int value)
{
    QProgressBar::setValue(value);
    if (m_isWorking)
        return;
    double target = 0.0;
    int range = maximum() - minimum();
    if (range > 0)
        target = static_cast<double>(value - minimum()) / static_cast<double>(range);
    target = qBound(0.0, target, 1.0);
    m_valueAnim->stop();
    m_valueAnim->setStartValue(m_animProgress);
    m_valueAnim->setEndValue(target);
    m_valueAnim->start();
}

void FluProgressBar::setState(State state)
{
    if (m_state == state)
        return;
    m_state = state;
    update();
}

FluProgressBar::State FluProgressBar::getState() const
{
    return m_state;
}

double FluProgressBar::getDeterminateOpacity() const
{
    return m_determinateOpacity;
}

void FluProgressBar::setDeterminateOpacity(double v)
{
    m_determinateOpacity = v;
    m_indeterminateOpacity = 1.0 - v;  // inverse for smooth transition
    update();
}

void FluProgressBar::onThemeChanged()
{
    update();
}

void FluProgressBar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const int w = width();
    const int h = height();  // should be 3

    // Theme colors. Track is always fully visible; only the fill/indicator
    // cross-fades between determinate and indeterminate via opacities below.
    QColor trackColor;
    QColor chunkColor;

    if (FluThemeUtils::isAtomOneDarkTheme())
    {
        trackColor = QColor(255, 255, 255, 139);          // #8BFFFFFF
        chunkColor = QColor(82, 139, 255);                // accent
    }
    else if (FluThemeUtils::isDarkTheme())
    {
        trackColor = QColor(255, 255, 255, 139);          // #8BFFFFFF
        chunkColor = QColor(118, 185, 237);               // accent
    }
    else  // Light
    {
        trackColor = QColor(0, 0, 0, 114);                // #72000000
        chunkColor = QColor(0, 90, 158);                  // accent
    }

    // Handle Error/Paused state colors
    if (m_state == State::Error)
    {
        chunkColor = FluThemeUtils::isDarkTheme() ? QColor(255, 153, 164)   // #FF99A4
                                                  : QColor(121, 35, 39);    // #792327
    }
    else if (m_state == State::Paused)
    {
        chunkColor = QColor(252, 225, 0);  // #FCE100 for both themes
    }

    // 1. Draw track: 1px line centered in 3px height
    const int trackTop = (h - 1) / 2;  // centered 1px line
    const qreal trackRadius = 0.5;     // WinUI3 track corner radius

    painter.setPen(Qt::NoPen);
    painter.setBrush(trackColor);
    painter.drawRoundedRect(QRectF(0, trackTop, w, 1), trackRadius, trackRadius);

    // 2. Draw fill/indicator
    if (m_isWorking)
    {
        // Indeterminate: dual chunk staggered animation
        const qreal barRadius = 1.5;  // WinUI3 bar corner radius
        QColor chunkColorIndeterminate = chunkColor;
        chunkColorIndeterminate.setAlpha(int(chunkColor.alpha() * m_indeterminateOpacity));

        painter.setBrush(chunkColorIndeterminate);

        // Chunk 1
        if (m_chunk1Pos > -0.4 && m_chunk1Pos < 1.0)
        {
            qreal chunkW = w * 0.4;  // 40% width
            qreal chunkX = m_chunk1Pos * w;
            painter.drawRoundedRect(QRectF(chunkX, 0, chunkW, h), barRadius, barRadius);
        }

        // Chunk 2 (delayed)
        if (m_chunk2Pos > -0.4 && m_chunk2Pos < 1.0)
        {
            qreal chunkW = w * 0.4;
            qreal chunkX = m_chunk2Pos * w;
            painter.drawRoundedRect(QRectF(chunkX, 0, chunkW, h), barRadius, barRadius);
        }
    }
    else
    {
        // Determinate: animated fill
        const double fillRatio = m_animProgress;
        if (fillRatio > 0.0)
        {
            const qreal fillW = w * fillRatio;
            const qreal barRadius = 1.5;  // WinUI3 bar corner radius
            QColor fillColor = chunkColor;
            fillColor.setAlpha(int(255 * m_determinateOpacity));
            painter.setBrush(fillColor);
            painter.drawRoundedRect(QRectF(0, 0, fillW, h), barRadius, barRadius);
        }
    }
}
