#pragma once

#include <QStackedLayout>
#include <QMap>
#include <QWidget>

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

    void removeWidget(QString str, QWidget *w);

    void setCurrentWidget(QString str);

  protected:
    QMap<QString, QWidget *> m_widgetMap;
};
