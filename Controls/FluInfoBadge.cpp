#include "FluInfoBadge.h"

FluInfoBadge::FluInfoBadge(QWidget* parent /*= nullptr*/) : QLabel(parent)
{
    setWordWrap(true);
    // setAlignment(Qt::AlignCenter);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    m_parent = nullptr;
    m_target = nullptr;
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluInfoBadge::setParent(QWidget* parent)
{
    QLabel::setParent(parent);
    m_parent = parent;
}

void FluInfoBadge::setTarget(QWidget* target)
{
    m_target = target;
}

QWidget* FluInfoBadge::getTarget()
{
    return m_target;
}

QColor FluInfoBadge::getBadgeColor()
{
    return m_badgeColor;
}

void FluInfoBadge::setBadgeColor(QColor color)
{
    m_badgeColor = color;
}

bool FluInfoBadge::eventFilter(QObject* watched, QEvent* event)
{
    if (m_parent == nullptr || m_target == nullptr)
        return QLabel::eventFilter(watched, event);

    if (watched == m_target)
    {
        if (event->type() == QEvent::Resize || event->type() == QEvent::Move)
        {
            move(m_target->x() + m_target->width() - width() / 2, m_target->y() - height() / 2);
        }
    }

    return QLabel::eventFilter(watched, event);
}

void FluInfoBadge::setInfoBadge(QWidget* parent, QWidget* target, FluInfoBadgeLevel level, int nVlaue /*= 0*/)
{
    if (parent == nullptr || target == nullptr)
        return;

    QString valueText = QString::asprintf("%d", nVlaue);
    if (nVlaue > 99)
    {
        valueText = QString::asprintf("%d+", 99);
    }

    FluInfoBadge* infoBadge = new FluInfoBadge(parent);
    infoBadge->setText(valueText);
    infoBadge->setLevel(level);
    infoBadge->adjustSize();

    infoBadge->setParent(parent);
    infoBadge->setTarget(target);

    target->installEventFilter(infoBadge);
    infoBadge->move(target->x() + target->width() - infoBadge->width() / 2, target->y() - infoBadge->height() / 2);
}

void FluInfoBadge::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.setBrush(getBadgeColor());
    // int nR = height() / 2;
    painter.drawRoundedRect(rect(), height() / 2, height() / 2);
    QLabel::paintEvent(event);
}
