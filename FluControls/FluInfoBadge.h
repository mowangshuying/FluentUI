#pragma once

#include <QLabel>
#include "../FluUtils/FluUtils.h"
#include <QEvent>

class FluInfoBadge : public QLabel
{
    Q_OBJECT
  public:
    FluInfoBadge(QWidget* parent = nullptr) : QLabel(parent)
    {
        setWordWrap(true);
        setAlignment(Qt::AlignCenter);
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluInfoBadge.qss", this, true);
        m_parent = nullptr;
        m_target = nullptr;
    }

    void setParent(QWidget* parent)
    {
        QLabel::setParent(parent);
        m_parent = parent;
    }

    void setTarget(QWidget* target)
    {
        m_target = target;
    }

    QWidget* getTarget()
    {
        return m_target;
    }

    bool eventFilter(QObject* watched, QEvent* event)
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

    static void setInfoBadge(QWidget* parent, QWidget* target, int nVlaue = 0)
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

  protected:
    QWidget* m_parent;
    QWidget* m_target;
};
