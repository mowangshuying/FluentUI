#pragma once

#include <QScrollArea>
#include <QHBoxLayout>

#include "FluTabBarItem.h"
#include <QScrollBar>
#include <QWheelEvent>

class FluTabBar : public QScrollArea
{
    Q_OBJECT
  public:
      FluTabBar(QWidget* parent = nullptr) : QScrollArea(parent)
      {
          setWidgetResizable(true);
          verticalScrollBar()->setEnabled(false);
          horizontalScrollBar()->setEnabled(true);

      //    verticalScrollBar()->scroll()
          setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
          setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

          m_hMainWidget = new QWidget(this);
          setWidget(m_hMainWidget);

          m_hMainLayout = new QHBoxLayout;
          m_hMainWidget->setLayout(m_hMainLayout);
          m_hMainLayout->setContentsMargins(0, 0, 0, 0);

          m_hLeftLayout = new QHBoxLayout;
          m_hMidLayout = new QHBoxLayout;
          m_hRightLayout = new QHBoxLayout;

          m_hMidLayout->setSpacing(0);

          m_hMidLayout->setAlignment(Qt::AlignLeft);

          m_hMainLayout->addLayout(m_hLeftLayout,0);
          m_hMainLayout->addLayout(m_hMidLayout, 0);
          m_hMainLayout->addLayout(m_hRightLayout,1);

          m_hMainWidget->setFixedHeight(40);
          setFixedHeight(40);

      }

      void addBarItem(FluTabBarItem* item)
      {
          insertTabBarItem(-1, item);
      }

      void insertTabBarItem(int nPos, FluTabBarItem* item)
      {
          if ((nPos < -1) && (nPos > (int)(m_tabBarItems.size())))
          {
              return;
          }

          if (nPos == -1)
          {
              nPos = m_tabBarItems.size();
          }

          // insert to widget
          m_hMidLayout->insertWidget(nPos, item);
          m_tabBarItems.insert(m_tabBarItems.begin() + nPos, item);
      }

      int getTabBarItemMaxWidth()
      {
          return m_nTabBarItemMaxWidth;
      }

      void setTabBarItemMaxWidth(int nW)
      {
          m_nTabBarItemMaxWidth = nW;
      }

      int getTabBarItemMinWidth()
      {
          return m_nTabBarItemMinWidth;
      }

      void setTabBarItemMinWidth(int nW)
      {
          m_nTabBarItemMinWidth = nW;
      }


      void wheelEvent(QWheelEvent* event)
      {
          // the "H" scroll Event;
          QPointF pos(0,0);
          QPointF gPos(0,0);
          QPoint pixelDelta(0,0);
          QPoint angleDelta(event->angleDelta().y(), 0);
          QWheelEvent wheelEvent(pos,gPos,pixelDelta,angleDelta,event->buttons(), event->modifiers(), event->phase(), event->inverted());
          QScrollArea::wheelEvent(&wheelEvent);
      }
  protected:
      QWidget* m_hMainWidget;
      QHBoxLayout* m_hMainLayout;
      QHBoxLayout* m_hLeftLayout;
      QHBoxLayout* m_hMidLayout;
      QHBoxLayout* m_hRightLayout;

      int m_nTabBarItemMaxWidth;
      int m_nTabBarItemMinWidth;

      QPoint m_dragPoint;
      bool m_bDraging;
      std::vector<FluTabBarItem*> m_tabBarItems;
};
