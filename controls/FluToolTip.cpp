#include "FluToolTip.h"
#include <QPainter>
#include <QPainterPath>
#include <QApplication>
#include <QScreen>

FluToolTip::FluToolTip(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setAttribute(Qt::WA_TranslucentBackground);
    setMaximumWidth(320);
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

    // Hover delay timer (1000ms before showing)
    m_delayTimer = new QTimer(this);
    m_delayTimer->setSingleShot(true);
    m_delayTimer->setInterval(1000);
    connect(m_delayTimer, &QTimer::timeout, this, [this]() { showToolTip(); });

    // Duration timer (5000ms auto-hide)
    m_durationTimer = new QTimer(this);
    m_durationTimer->setSingleShot(true);
    m_durationTimer->setInterval(5000);
    connect(m_durationTimer, &QTimer::timeout, this, [this]() { hideToolTip(); });

    // Fade animation (167ms)
    m_fadeAnim = new QPropertyAnimation(this, "opacity", this);
    m_fadeAnim->setDuration(167);
    m_fadeAnim->setEasingCurve(QEasingCurve::OutCubic);
    connect(m_fadeAnim, &QPropertyAnimation::finished, this, [this]() {
        if (m_opacity <= 0.0)
            hide();
    });

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme) { onThemeChanged(); });
}

FluToolTip::~FluToolTip()
{
    if (m_target)
    {
        m_target->removeEventFilter(this);
    }
}

FluToolTip* FluToolTip::setToolTip(QWidget* parent, QWidget* target, const QString& text, Placement placement /*= Placement::Bottom*/)
{
    if (parent == nullptr || target == nullptr)
        return nullptr;

    FluToolTip* tip = new FluToolTip(parent);
    tip->m_text = text;
    tip->m_target = target;
    tip->m_placement = placement;
    target->installEventFilter(tip);

    // Clear target reference when target is destroyed. Lifetime of the tooltip
    // itself is managed by its parent (Qt object tree), never delete manually.
    connect(target, &QObject::destroyed, tip, [tip](QObject*) {
        tip->m_target = nullptr;
        tip->hide();
    });

    return tip;
}

void FluToolTip::setText(const QString& text)
{
    if (m_text != text)
    {
        m_text = text;
        adjustSize();
        reposition();
        update();
    }
}

QString FluToolTip::getText() const
{
    return m_text;
}

double FluToolTip::getOpacity() const
{
    return m_opacity;
}

void FluToolTip::setOpacity(double opacity)
{
    if (!qFuzzyCompare(m_opacity + 1, opacity + 1))
    {
        m_opacity = opacity;
        update();
    }
}

void FluToolTip::showToolTip()
{
    if (m_target == nullptr)
        return;

    // Resize to fit content with padding
    QFontMetrics fm(font());
    QRect textBound(0, 0, maximumWidth() - 18, 10000);
    QRect textRect = fm.boundingRect(textBound, Qt::TextWordWrap | Qt::AlignLeft | Qt::AlignVCenter, m_text);
    int w = qMin(textRect.width() + 18, maximumWidth());
    int h = textRect.height() + 14;
    setFixedSize(w, h);

    reposition();
    m_opacity = 0.0;
    show();
    raise();

    // Fade in
    if (m_fadeAnim)
    {
        m_fadeAnim->stop();
        m_fadeAnim->setStartValue(0.0);
        m_fadeAnim->setEndValue(1.0);
        m_fadeAnim->start();
    }

    // Start auto-hide duration timer
    if (m_durationTimer)
    {
        m_durationTimer->start();
    }
}

void FluToolTip::hideToolTip()
{
    if (!isVisible())
        return;

    if (m_durationTimer)
        m_durationTimer->stop();

    // Fade out then hide
    if (m_fadeAnim)
    {
        m_fadeAnim->stop();
        m_fadeAnim->setStartValue(m_opacity);
        m_fadeAnim->setEndValue(0.0);
        m_fadeAnim->start();
    }
    else
    {
        m_opacity = 0.0;
        hide();
    }
}

void FluToolTip::setPlacement(Placement placement)
{
    if (m_placement == placement)
        return;
    m_placement = placement;
    if (isVisible())
        reposition();
}

FluToolTip::Placement FluToolTip::getPlacement() const
{
    return m_placement;
}

void FluToolTip::reposition()
{
    if (!m_target)
        return;

    const int gap = 8;
    const QRect targetRect(m_target->mapToGlobal(QPoint(0, 0)), m_target->size());
    const int w = width();
    const int h = height();

    QPoint pos;
    switch (m_placement)
    {
        case Placement::Top:
            pos = QPoint(targetRect.center().x() - w / 2, targetRect.top() - h - gap);
            break;
        case Placement::TopLeft:
            pos = QPoint(targetRect.left() - w - gap, targetRect.top() - h - gap);
            break;
        case Placement::TopRight:
            pos = QPoint(targetRect.right() + gap, targetRect.top() - h - gap);
            break;
        case Placement::Bottom:
            pos = QPoint(targetRect.center().x() - w / 2, targetRect.bottom() + gap);
            break;
        case Placement::BottomLeft:
            pos = QPoint(targetRect.left() - w - gap, targetRect.bottom() + gap);
            break;
        case Placement::BottomRight:
            pos = QPoint(targetRect.right() + gap, targetRect.bottom() + gap);
            break;
        case Placement::Left:
            pos = QPoint(targetRect.left() - w - gap, targetRect.center().y() - h / 2);
            break;
        case Placement::Right:
            pos = QPoint(targetRect.right() + gap, targetRect.center().y() - h / 2);
            break;
    }

    QScreen* screen = QApplication::screenAt(targetRect.center());
    if (screen)
    {
        QRect screenGeom = screen->availableGeometry();

        // Default Bottom placement: flip above the target if it overflows below
        if (m_placement == Placement::Bottom && pos.y() + h > screenGeom.bottom() && targetRect.top() - h - gap >= screenGeom.top())
            pos.setY(targetRect.top() - h - gap);

        pos.setX(qBound(screenGeom.left(), pos.x(), screenGeom.right() - w));
        pos.setY(qBound(screenGeom.top(), pos.y(), screenGeom.bottom() - h));
    }

    move(pos);
}

void FluToolTip::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setOpacity(m_opacity);

    QPainterPath path;
    const qreal r = 4.0;
    path.addRoundedRect(rect().adjusted(1, 1, -1, -1), r, r);
    painter.setClipPath(path);

    // Background: use window role color (set by QSS background-color)
    painter.fillPath(path, palette().window());

    // Border
    painter.setPen(QPen(palette().mid(), 1));
    painter.drawPath(path);

    // Text (WindowText role is set by QSS color)
    painter.setPen(palette().windowText().color());
    painter.drawText(rect().adjusted(9, 6, -9, -8), Qt::TextWordWrap | Qt::AlignLeft | Qt::AlignVCenter, m_text);
}

void FluToolTip::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluToolTip.qss", this, FluThemeUtils::getUtils()->getTheme());
}

bool FluToolTip::eventFilter(QObject* obj, QEvent* e)
{
    if (obj == nullptr || obj != m_target)
        return QWidget::eventFilter(obj, e);

    switch (e->type())
    {
        case QEvent::HoverEnter:
        case QEvent::Enter:
            if (m_delayTimer)
                m_delayTimer->start();
            break;

        case QEvent::HoverLeave:
        case QEvent::Leave:
        case QEvent::MouseButtonPress:
            if (m_delayTimer)
                m_delayTimer->stop();
            hideToolTip();
            break;

        case QEvent::Hide:
        case QEvent::ParentChange:
            hideToolTip();
            break;

        case QEvent::Resize:
        case QEvent::Move:
            if (isVisible())
                reposition();
            break;

        default:
            break;
    }

    return QWidget::eventFilter(obj, e);
}
