#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include "FluVNavigationItem.h"
#include "../FluUtils/FluUtils.h"

class FluVNavigationMenuItem : public FluVNavigationItem
{
    Q_OBJECT
  public:
    FluVNavigationMenuItem(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  signals:
    void menuItemClicked();
  public slots:
    void onThemeChanged();

  protected:
    QPushButton *m_menuButton;
    QHBoxLayout *m_hLayout;

    QWidget *m_wrapWidget1;
    QHBoxLayout *m_hWrapWidgetLayout1;
    QWidget *m_wrapWidget2;
};
