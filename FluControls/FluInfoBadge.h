#pragma once

#include <QLabel>
#include "../FluUtils/FluUtils.h"
#include <QEvent>

class FluInfoBadge : public QLabel
{
    Q_OBJECT
  public:
    FluInfoBadge(QWidget* parent = nullptr);

    void setParent(QWidget* parent);

    void setTarget(QWidget* target);

    QWidget* getTarget();

    bool eventFilter(QObject* watched, QEvent* event);

    static void setInfoBadge(QWidget* parent, QWidget* target, int nVlaue = 0);

  protected:
    QWidget* m_parent;
    QWidget* m_target;
};
