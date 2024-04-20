#pragma once

#include <QWidget>

#include "FluTabBar.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QStackedLayout>
#include "../FluUtils/FluUtils.h"
#include <QWidget>
#include "FluStackedLayout.h"
#include <QStyleOption>
#include <QPainter>

class FluTabView : public QWidget
{
    Q_OBJECT
  public:
    FluTabView(QWidget* parent = nullptr);

    void addTab(QString tabString, QWidget* tabWidget);

    bool eventFilter(QObject* watched, QEvent* event);

    void paintEvent(QPaintEvent* event);

  signals:
    void addTabBtnClicked();

  protected:
    QVBoxLayout* m_vMainLayout;
    FluTabBar* m_tabBar;

    QWidget* m_sWidgt;
    FluStackedLayout* m_sLayout;
};
