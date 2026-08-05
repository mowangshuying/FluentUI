#include "FluInfoBadge.h"
#include <QPainter>
#include <QPainterPath>
#include <QTransform>

FluInfoBadge::FluInfoBadge(QWidget* parent /*= nullptr*/) : QLabel(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setAlignment(Qt::AlignCenter);

    // Value pop animation
    m_valueAnimation = new QPropertyAnimation(this, "animScale", this);
    m_valueAnimation->setDuration(180);
    m_valueAnimation->setEasingCurve(QEasingCurve::OutBack);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme) { onThemeChanged(); });
}

FluInfoBadge::~FluInfoBadge()
{
    if (m_target)
    {
        m_target->removeEventFilter(this);
    }
}

void FluInfoBadge::setTarget(QWidget* target)
{
    if (m_target == target)
        return;
    if (m_target)
    {
        m_target->removeEventFilter(this);
        disconnect(m_target, nullptr, this, nullptr);
    }
    m_target = target;
    if (m_target)
    {
        m_target->installEventFilter(this);
        connect(m_target, &QObject::destroyed, this, [this](QObject*) {
            m_target = nullptr;
            delete this;
        });
    }
}

QWidget* FluInfoBadge::getTarget() const
{
    return m_target;
}

QColor FluInfoBadge::getBadgeColor() const
{
    return m_badgeColor;
}

void FluInfoBadge::setBadgeColor(QColor color)
{
    if (m_badgeColor != color)
    {
        m_badgeColor = color;
        update();
    }
}

int FluInfoBadge::getValue() const
{
    return m_value;
}

void FluInfoBadge::setValue(int value)
{
    m_value = value;
    updateText();
    adjustSize();
    updateVisibility();
    reposition();

    // Trigger pop animation if value changed
    if (m_valueAnimation)
    {
        m_valueAnimation->stop();
        m_valueAnimation->setStartValue(0.6);
        m_valueAnimation->setEndValue(1.0);
        m_valueAnimation->start();
    }
}

FluInfoBadgeLevel FluInfoBadge::getLevel() const
{
    return m_level;
}

void FluInfoBadge::setLevel(FluInfoBadgeLevel level)
{
    if (m_level == level)
        return;
    m_level = level;
    updateLevelProperty();
    updateText();
    adjustSize();
    updateVisibility();
    reposition();
}

qreal FluInfoBadge::getAnimScale() const
{
    return m_animScale;
}

void FluInfoBadge::setAnimScale(qreal scale)
{
    if (!qFuzzyCompare(m_animScale + 1, scale + 1))
    {
        m_animScale = scale;
        update();
    }
}

bool FluInfoBadge::eventFilter(QObject* watched, QEvent* event)
{
    if (m_target == nullptr)
        return QLabel::eventFilter(watched, event);

    if (watched == m_target)
    {
        switch (event->type())
        {
            case QEvent::Resize:
            case QEvent::Move:
                reposition();
                break;
            case QEvent::Hide:
                hide();
                break;
            case QEvent::Show:
                updateVisibility();
                break;
            case QEvent::ParentChange:
                delete this;
                return true;
            default:
                break;
        }
    }

    return QLabel::eventFilter(watched, event);
}

FluInfoBadge* FluInfoBadge::setInfoBadge(QWidget* parent, QWidget* target, FluInfoBadgeLevel level, int value /*= 0*/)
{
    if (parent == nullptr || target == nullptr)
        return nullptr;

    FluInfoBadge* badge = new FluInfoBadge(parent);
    badge->m_value = value;
    badge->m_level = level;
    badge->updateLevelProperty();
    badge->updateText();
    badge->adjustSize();
    badge->setTarget(target);
    badge->updateVisibility();
    badge->reposition();
    return badge;
}

void FluInfoBadge::reposition()
{
    if (!parentWidget() || !m_target)
        return;
    int x = m_target->x() + m_target->width() - width() / 2;
    int y = m_target->y() - height() / 2;

    // Clamp within parent bounds
    int parentW = parentWidget()->width();
    if (x + width() > parentW)
        x = parentW - width();
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;

    move(x, y);
}

void FluInfoBadge::updateText()
{
    if (m_value > 99)
        setText("99+");
    else
        setText(QString::number(m_value));
}

void FluInfoBadge::updateVisibility()
{
    if (m_target && !m_target->isVisible())
    {
        hide();
        return;
    }
    if (m_value <= 0)
        hide();
    else
        show();
}

void FluInfoBadge::updateLevelProperty()
{
    QString levelString;
    switch (m_level)
    {
        case FluInfoBadgeLevel::Info:
            levelString = "Info";
            break;
        case FluInfoBadgeLevel::Suc:
            levelString = "Suc";
            break;
        case FluInfoBadgeLevel::Warn:
            levelString = "Warn";
            break;
        case FluInfoBadgeLevel::Error:
            levelString = "Error";
            break;
        default:
            break;
    }
    setProperty("level", levelString);
    style()->polish(this);
}

void FluInfoBadge::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    const qreal h = height();
    const qreal w = width();
    const qreal radius = h / 2.0;

    // Center-scale transform
    painter.save();
    painter.translate(w / 2.0, h / 2.0);
    painter.scale(m_animScale, m_animScale);
    painter.translate(-w / 2.0, -h / 2.0);

    QRectF paintRect(0.25, 0.25, w - 0.5, h - 0.5);

    // White border stroke
    QPen borderPen;
    borderPen.setColor(Qt::white);
    borderPen.setWidthF(0.5);
    painter.setPen(borderPen);
    painter.setBrush(getBadgeColor());
    painter.drawRoundedRect(paintRect, radius, radius);

    // Text
    painter.setPen(palette().color(QPalette::WindowText));
    painter.drawText(paintRect.adjusted(3, 1, -3, -1), Qt::AlignCenter, text());

    painter.restore();
}
