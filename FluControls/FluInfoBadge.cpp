#include "FluInfoBadge.h"

FluInfoBadge::FluInfoBadge(QWidget* parent /*= nullptr*/) : QLabel(parent)
{
    setWordWrap(true);
    setAlignment(Qt::AlignCenter);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluInfoBadge.qss", this);
    m_parent = nullptr;
    m_target = nullptr;
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

void FluInfoBadge::setInfoBadge(QWidget* parent, QWidget* target, int nVlaue /*= 0*/)
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
    infoBadge->adjustSize();

    infoBadge->setParent(parent);
    infoBadge->setTarget(target);

    target->installEventFilter(infoBadge);
    infoBadge->move(target->x() + target->width() - infoBadge->width() / 2, target->y() - infoBadge->height() / 2);
}
