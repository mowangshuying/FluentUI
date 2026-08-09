#include "FluRatingControl.h"
#include <QMouseEvent>

#include <QtMath>

FluRatingControl::FluRatingControl(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setFixedSize(170, 45);
    setMouseTracking(true);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [this](FluTheme) { onThemeChanged(); });
}

double FluRatingControl::getValue() const
{
    return m_value;
}

void FluRatingControl::setValue(double value)
{
    value = qBound(0.0, value, static_cast<double>(m_maxRating));
    value = qRound(value * 2.0) / 2.0;  // snap to 0.5 step
    if (qFuzzyCompare(m_value, value))
        return;
    m_value = value;
    emit valueChanged(m_value);
    update();
}

bool FluRatingControl::isReadOnly() const
{
    return m_readOnly;
}

void FluRatingControl::setReadOnly(bool readOnly)
{
    m_readOnly = readOnly;
}

bool FluRatingControl::isClearEnabled() const
{
    return m_clearEnabled;
}

void FluRatingControl::setClearEnabled(bool clearEnabled)
{
    m_clearEnabled = clearEnabled;
}

double FluRatingControl::starValueAt(const QPoint& pos) const
{
    const int starSize = 25;
    const int spacing = 8;
    const int totalW = m_maxRating * starSize + (m_maxRating - 1) * spacing;
    const int startX = (width() - totalW) / 2;

    for (int i = 0; i < m_maxRating; ++i)
    {
        const int starLeft = startX + i * (starSize + spacing);
        const int starRight = starLeft + starSize + spacing;  // cell includes trailing spacing
        if (pos.x() < starRight)
        {
            const int starCenter = starLeft + starSize / 2;
            if (pos.x() <= starCenter)
                return i + 0.5;  // left half
            return i + 1.0;      // right half (or trailing gap -> full star)
        }
    }
    return m_maxRating;
}

QPainterPath FluRatingControl::starPath(const QRectF& rect) const
{
    QPainterPath path;
    const QPointF center = rect.center();
    const double outer = rect.width() / 2.0 * 0.92;
    const double inner = outer * 0.382;

    for (int i = 0; i < 10; ++i)
    {
        const double radius = (i % 2 == 0) ? outer : inner;
        const double angle = qDegreesToRadians(-90.0 + i * 36.0);
        const QPointF pt(center.x() + radius * qCos(angle), center.y() + radius * qSin(angle));
        if (i == 0)
            path.moveTo(pt);
        else
            path.lineTo(pt);
    }
    path.closeSubpath();
    return path;
}

void FluRatingControl::drawStar(QPainter& painter, const QRectF& rect, double fraction, const QColor& fillColor, const QColor& emptyColor) const
{
    const QPainterPath path = starPath(rect);

    // Empty background
    painter.setPen(QPen(emptyColor, 1.5));
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);

    if (fraction <= 0.0)
        return;

    // Filled portion (clipped on the left side by `fraction`)
    painter.save();
    painter.setClipRect(QRectF(rect.left(), rect.top(), rect.width() * fraction, rect.height()));
    painter.setPen(Qt::NoPen);
    painter.setBrush(fillColor);
    painter.drawPath(path);
    painter.restore();
}

void FluRatingControl::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const int starSize = 25;
    const int spacing = 8;
    const int totalW = m_maxRating * starSize + (m_maxRating - 1) * spacing;
    const int startX = (width() - totalW) / 2;
    const int y = (height() - starSize) / 2;

    QColor accent;
    QColor emptyColor;
    if (FluThemeUtils::isAtomOneDarkTheme())
    {
        accent = QColor(82, 139, 255);
        emptyColor = QColor(120, 124, 130);
    }
    else if (FluThemeUtils::isDarkTheme())
    {
        accent = QColor(118, 185, 237);
        emptyColor = QColor(150, 150, 154);
    }
    else
    {
        accent = QColor(0, 90, 158);
        emptyColor = QColor(169, 169, 174);
    }

    double displayValue = m_value;
    if (m_hoverValue >= 0.0)
        displayValue = m_hoverValue;

    for (int i = 0; i < m_maxRating; ++i)
    {
        const QRectF starRect(startX + i * (starSize + spacing), y, starSize, starSize);

        if (displayValue <= i)
        {
            // Empty star
            drawStar(painter, starRect, 0.0, accent, emptyColor);
        }
        else if (displayValue >= i + 1.0)
        {
            // Full star
            drawStar(painter, starRect, 1.0, accent, emptyColor);
        }
        else
        {
            // Partial (half) star
            drawStar(painter, starRect, displayValue - i, accent, emptyColor);
        }
    }
}

void FluRatingControl::mousePressEvent(QMouseEvent* event)
{
    if (m_readOnly || event->button() != Qt::LeftButton)
        return;

    const double v = starValueAt(event->pos());
    if (m_clearEnabled && m_value > 0.0 && qFuzzyCompare(v, m_value) && v > 0.0)
    {
        // Clicking the star that represents the current value clears it
        setValue(0.0);
    }
    else
    {
        setValue(v);
    }
    m_hoverValue = m_value;
    update();
}

void FluRatingControl::mouseMoveEvent(QMouseEvent* event)
{
    if (m_readOnly)
    {
        QWidget::mouseMoveEvent(event);
        return;
    }
    const double v = starValueAt(event->pos());
    if (!qFuzzyCompare(m_hoverValue, v))
    {
        m_hoverValue = v;
        update();
    }
}

void FluRatingControl::leaveEvent(QEvent* event)
{
    m_hoverValue = -1.0;
    update();
    FluWidget::leaveEvent(event);
}

void FluRatingControl::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluRatingControl.qss", this, FluThemeUtils::getUtils()->getTheme());
    update();
}