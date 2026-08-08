#pragma once

#include "FluWidget.h"
#include "FluTabBarContent.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QPushButton>
#include <QThread>

class FluTabBar : public FluWidget
{
    Q_OBJECT
  public:
    FluTabBar(QWidget* parent = nullptr);

    std::vector<FluTabBarItem*> getTabBarItems();

    QColor getSelectedTabColor() const;

    void addBarItem(FluTabBarItem* item);

    void removeTabBarItem(FluTabBarItem* item);

    void resizeEvent(QResizeEvent* event);

    void paintEvent(QPaintEvent* event);

    void adjustAddTabButtonPosition();

  signals:
    void addTabButtonClicked();
  public slots:
    void onThemeChanged();

  private:
    void animateItemIn(FluTabBarItem* item);
    void animateItemOut(FluTabBarItem* item);

  protected:
    QHBoxLayout* m_mainLayout;
    FluTabBarContent* m_tabBarContent;
    QPushButton* m_addTabButton;
    FluTabBarItem* m_animatingItem = nullptr;
};
