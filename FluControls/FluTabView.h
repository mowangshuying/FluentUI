#pragma once

#include "FluWidget.h"

#include "FluTabBar.h"
#include "FluWidget.h"
#include <QVBoxLayout>
#include <QStackedLayout>
#include "../FluUtils/FluUtils.h"
#include "FluWidget.h"
#include "FluStackedLayout.h"
#include <QStyleOption>
#include <QPainter>

class FluTabView : public FluWidget
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
