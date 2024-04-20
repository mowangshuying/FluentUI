#pragma once

#include <QWidget>
#include "FluTabBarContent.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QPushButton>

class FluTabBar : public QWidget
{
    Q_OBJECT
  public:
      FluTabBar(QWidget* parent = nullptr) : QWidget(parent)
      {
          m_hMainLayout = new QHBoxLayout;
          setLayout(m_hMainLayout);
          m_hMainLayout->setAlignment(Qt::AlignLeft);

          m_hMainLayout->setSpacing(0);
          m_hMainLayout->setContentsMargins(10, 0, 10, 0);
          m_hMainLayout->setSizeConstraint(QHBoxLayout::SetMinAndMaxSize);

          m_tabBarContent = new FluTabBarContent;
          m_tabBarContent->resize(0,height());
          m_hMainLayout->addWidget(m_tabBarContent);

          m_hMainLayout->addSpacing(8);

          m_addTabBtn = new QPushButton(this);
          m_addTabBtn->setFixedSize(30, 30);
          m_addTabBtn->setIconSize(QSize(20, 20));
          m_addTabBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Add));
          m_addTabBtn->setObjectName("addTabBtn");
          m_hMainLayout->addWidget(m_addTabBtn);

          

       //   m_hMainLayout->addStretch(1);
          connect(m_addTabBtn, &QPushButton::clicked, [=]() { emit addTabBtnClicked();
          });

          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTabBar.qss", this);
      }
      
      std::vector<FluTabBarItem*> getTabBarItems()
      {
          return m_tabBarContent->getTabBarItems();
      }


      void addBarItem(FluTabBarItem* item)
      {
          m_tabBarContent->addBarItem(item);
      }

      void resizeEvent(QResizeEvent* event)
      {
          //m_tabBarContent->setMinimumWidth(0);
      }

      void paintEvent(QPaintEvent* event)
      {
          QStyleOption opt;
          opt.initFrom(this);
          QPainter painter(this);
          style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }
signals:
      void addTabBtnClicked();
  protected:
      QHBoxLayout* m_hMainLayout;
      FluTabBarContent* m_tabBarContent;
      QPushButton* m_addTabBtn;
};
