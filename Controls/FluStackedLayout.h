#pragma once

#include <QStackedLayout>
#include <QMap>
#include "FluWidget.h"
#include <QPropertyAnimation>

// use it only contains widgets
// when use it, please just use addWidget , removeWidget
// can't support insertWidget and other add widget methods.
class FluStackedLayout : public QStackedLayout
{
    Q_OBJECT
  public:
    FluStackedLayout();
    FluStackedLayout(QWidget *parent);
    FluStackedLayout(QLayout *parentLayout);

    void addWidget(QString str, QWidget *w);

    int addWidget(QWidget *w);

    void removeWidget(QString str, QWidget *w);

    void setCurrentWidget(QString str);

    QWidget *getWidget(QString str);

  protected:
    QMap<QString, QWidget *> m_widgetMap;
    // QPropertyAnimation *m_animation;
};
