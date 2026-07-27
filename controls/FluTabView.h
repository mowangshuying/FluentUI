#pragma once

#include "FluWidget.h"

#include "FluTabBar.h"
#include "FluWidget.h"
#include <QVBoxLayout>
#include <QStackedLayout>
#include "../Utils/FluUtils.h"
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
    void addTabButtonClicked();

  protected:
    QVBoxLayout* m_mainLayout;
    FluTabBar* m_tabBar;

    QWidget* m_widgt;
    FluStackedLayout* m_layout;
};
