#include "FluProgressBar.h"

#include <QtMath>

FluProgressBar::FluProgressBar(QWidget* parent /*= nullptr*/) : QProgressBar(parent)
{
    setTextVisible(false);
    setMinimumHeight(3);
    setMaximumHeight(7);

    // Determinate: smooth value transition animation
    m_valueAnim = new QPropertyAnimation(this, "animProgress", this);
    m_valueAnim->setDuration(200);
    m_valueAnim->setEasingCurve(QEasingCurve::OutCubic);

    // Indeterminate: sliding chunk timer (~60 fps)
    m_indetTimer = new QTimer(this);
    m_indetTimer->setInterval(16);
    connect(m_indetTimer, &QTimer::timeout, this, [this]() {
        if (!m_isWorking)
            return;
        m_animProgress += 0.012;
        if (m_animProgress > 1.0)
            m_animProgress = 0.0;
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
    if (working)
    {
        m_animProgress = 0.0;
        m_indetTimer->start();
    }
    else
    {
        m_indetTimer->stop();
        // Restore determinate fill ratio on exit
        int range = maximum() - minimum();
        m_animProgress = (range > 0) ? static_cast<double>(value() - minimum()) / static_cast<double>(range) : 0.0;
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
    const int h = height();
    const qreal radius = h / 2.0;

    // Theme colors
    QColor trackColor(134, 134, 134);
    QColor chunkColor(0, 90, 158);
    if (FluThemeUtils::isDarkTheme())
    {
        trackColor = QColor(154, 154, 154);
        chunkColor = QColor(118, 185, 237);
    }
    if (FluThemeUtils::isAtomOneDarkTheme())
    {
        trackColor = QColor(154, 154, 154);
        chunkColor = QColor(82, 139, 255);
    }

    // Rounded track clip path (shared across both modes)
    QPainterPath clipPath;
    clipPath.addRoundedRect(QRectF(0, 0, w, h), radius, radius);

    // Track background
    painter.setPen(Qt::NoPen);
    painter.setBrush(trackColor);
    painter.drawRoundedRect(QRectF(0, 0, w, h), radius, radius);

    painter.setClipPath(clipPath);
    painter.setBrush(chunkColor);

    if (m_isWorking)
    {
        // Indeterminate: sliding chunk (~40% of bar width), eased left->right
        const qreal chunkW = w * 0.4;
        const double t = m_animProgress;
        const double eased = t < 0.5 ? 4.0 * t * t * t : 1.0 - qPow(-2.0 * t + 2.0, 3.0) / 2.0;
        const qreal chunkX = -chunkW + eased * (w + chunkW);
        painter.drawRoundedRect(QRectF(chunkX, 0, chunkW, h), radius, radius);
    }
    else
    {
        // Determinate: animated fill ratio
        const double fillRatio = m_animProgress;
        if (fillRatio > 0.0)
        {
            const qreal fillW = w * fillRatio;
            painter.drawRoundedRect(QRectF(0, 0, fillW, h), radius, radius);
        }
    }

    painter.setClipping(false);
}
