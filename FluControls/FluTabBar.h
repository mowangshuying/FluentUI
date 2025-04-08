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

    void addBarItem(FluTabBarItem* item);

    void removeTabBarItem(FluTabBarItem* item);

    void resizeEvent(QResizeEvent* event);

    void paintEvent(QPaintEvent* event);

    void adjustAddTabBtnPosition();

  signals:
    void addTabBtnClicked();
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTabBar.qss", this);
        else if (FluThemeUtils::isDarkTheme())
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTabBar.qss", this);
    }

  protected:
    QHBoxLayout* m_hMainLayout;
    FluTabBarContent* m_tabBarContent;
    QPushButton* m_addTabBtn;
};
