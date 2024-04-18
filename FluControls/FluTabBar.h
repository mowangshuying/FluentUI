#pragma once

#include <QWidget>
#include "FluTabBarContent.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>

class FluTabBar : public QWidget
{
    Q_OBJECT
  public:
      FluTabBar(QWidget* parent = nullptr) : QWidget(parent)
      {
          m_hMainLayout = new QHBoxLayout;
          setLayout(m_hMainLayout);

          m_hMainLayout->setSpacing(0);
          m_hMainLayout->setContentsMargins(10, 0, 10, 0);

          m_tabBarContent = new FluTabBarContent;
          m_hMainLayout->addWidget(m_tabBarContent);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTabBar.qss", this);
      }

      void addBarItem(FluTabBarItem* item)
      {
          m_tabBarContent->insertTabBarItem(-1, item);
      }

      void paintEvent(QPaintEvent* event)
      {
          QStyleOption opt;
          opt.initFrom(this);
          QPainter painter(this);
          style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

          // find a point.

      }

  protected:
      QHBoxLayout* m_hMainLayout;
      FluTabBarContent* m_tabBarContent;
};
