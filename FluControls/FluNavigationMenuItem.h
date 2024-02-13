#pragma once

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include "FluNavigationItem.h"
#include "../FluUtils/FluUtils.h"

class FluNavigationMenuItem : public FluNavigationItem
{
    Q_OBJECT
  public:
    FluNavigationMenuItem(QWidget *parent = nullptr);

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
};
