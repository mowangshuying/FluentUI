#pragma once

#include "FluWidget.h"

#include "FluTabBar.h"
#include "FluWidget.h"
#include <QVBoxLayout>
#include <QStackedLayout>
#include "../utils/FluUtils.h"
#include "FluWidget.h"
#include "FluStackedLayout.h"
#include <QStyleOption>
#include <QPainter>

class FluTabViewJunctionOverlay;

class FluTabView : public FluWidget
{
    Q_OBJECT
  public:
    FluTabView(QWidget* parent = nullptr);

    void addTab(QString tabString, QWidget* tabWidget);

    bool eventFilter(QObject* watched, QEvent* event);

    void paintEvent(QPaintEvent* event);

    void resizeEvent(QResizeEvent* event);

    FluTabBar* getTabBar() const { return m_tabBar; }
    QWidget* getContentWidget() const { return m_widgt; }

    QString qssFileName() override { return "FluTabView.qss"; }

    void updateJunctionOverlay();

  signals:
    void addTabButtonClicked();

  protected:
    QVBoxLayout* m_mainLayout;
    FluTabBar* m_tabBar;

    QWidget* m_widgt;
    FluStackedLayout* m_layout;

    FluTabViewJunctionOverlay* m_junctionOverlay = nullptr;
};
