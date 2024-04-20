#pragma once

#include <QScrollArea>
#include <QHBoxLayout>

#include "FluTabBarItem.h"
#include <QScrollBar>
#include <QWheelEvent>

class FluTabBarContent : public QScrollArea
{
    Q_OBJECT
  public:
      FluTabBarContent(QWidget* parent = nullptr) : QScrollArea(parent)
      {
          setWidgetResizable(true);
          verticalScrollBar()->setEnabled(false);
          horizontalScrollBar()->setEnabled(true);

          setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
          setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

          m_hMainWidget = new QWidget(this);
          setWidget(m_hMainWidget);

          m_hMainWidget->setObjectName("mainWidget");

          m_hMainLayout = new QHBoxLayout;
          m_hMainWidget->setLayout(m_hMainLayout);
          m_hMainLayout->setContentsMargins(0,4,0,0);

      //    m_hLeftLayout = new QHBoxLayout;
          m_hMidLayout = new QHBoxLayout;
    //      m_hRightLayout = new QHBoxLayout;

          m_hMidLayout->setSpacing(0);

          m_hMidLayout->setAlignment(Qt::AlignLeft);
       //   m_hRightLayout->setAlignment(Qt::AlignLeft);

          m_hMidLayout->setSizeConstraint(QHBoxLayout::SetMinAndMaxSize);

          //m_addTabBtn = new QPushButton;
          //m_addTabBtn->setFixedSize(30, 30);
          //m_addTabBtn->setIconSize(QSize(20, 20));
          //m_addTabBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Add));
          //m_addTabBtn->setObjectName("addTabBtn");
          //m_hRightLayout->addWidget(m_addTabBtn);
        //  m_hMainLayout->addLayout(m_hLeftLayout);
          m_hMainLayout->addLayout(m_hMidLayout);
       //   m_hMainLayout->addLayout(m_hRightLayout);
          m_hMainLayout->addStretch();

          m_hMainWidget->setFixedHeight(40);
          setFixedHeight(40);

          /*static int NUM = 0;
          connect(m_addTabBtn, &QPushButton::clicked, [=]() {
              auto item = new FluTabBarItem;

              QString tmpS = QString::asprintf("New Item %d", NUM * NUM * NUM);
              item->setText(tmpS);
              addBarItem(item);

              NUM++;
          });*/
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTabBarContent.qss", this);


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

          connect(item, &FluTabBarItem::clicked, [=]() {
              for (auto itemIter = m_tabBarItems.begin(); itemIter != m_tabBarItems.end(); itemIter++)
              {
                  (*itemIter)->setSelected(false);
                  (*itemIter)->style()->polish((*itemIter));
              }

              item->setSelected(true);
              item->style()->polish(item);
          });

          //adjustTabBarItemSize();
          
      }

      void removeTabBarItem(FluTabBarItem* item)
      {
          m_hMidLayout->removeWidget(item);
          auto itf = std::find(m_tabBarItems.begin(), m_tabBarItems.end(), item);
          if (itf != m_tabBarItems.end())
          {
              m_tabBarItems.erase(itf);
          }
          item->deleteLater();
      }

     // void adjustTabBarItemSize()
     // {
     //     if (m_tabBarItems.size() * 240 > width())
     //     {
     //         for (auto itemIter = m_tabBarItems.begin(); itemIter != m_tabBarItems.end(); itemIter++)
     //         {
     //             (*itemIter)->setFixedWidth(120);
     //         }
     //     }
     //     else
     //     {
     //         for (auto itemIter = m_tabBarItems.begin(); itemIter != m_tabBarItems.end(); itemIter++)
     //         {
     //             (*itemIter)->setFixedWidth(240);
     //         }
     //     }
     // }

      int getSelectedTabBarItemIndex()
      {
          int pos = -1;
          for (int i = 0; i < m_tabBarItems.size(); i++)
          {
              if (m_tabBarItems[i]->getSelected())
              {
                  pos = i;
                  break;
              }
          }
          return pos;
      }

      FluTabBarItem* getSelectedTabBarItem()
      {
          int itemIndex = getSelectedTabBarItemIndex();
          if (itemIndex < 0 || itemIndex >= m_tabBarItems.size())
              return nullptr;

          return m_tabBarItems[itemIndex];
      }

      std::vector<FluTabBarItem*> getTabBarItems()
      {
          return m_tabBarItems;
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


      void getDrawCenterPoint(QPoint &drawPLL, QPoint &drawPLR, QPoint &drawPRL, QPoint &drawPRR)
      {
          auto tabBarItem = getSelectedTabBarItem();
          if (tabBarItem == nullptr)
              return;

          QPoint tmpP;
          tmpP.setX(tabBarItem->x());
          tmpP.setY(tabBarItem->y() + tabBarItem->height());

          drawPLL.setX(tmpP.x() - 8);
          drawPLL.setY(tmpP.y() - 8);

          drawPLR.setX(tmpP.x() + 8);
          drawPLR.setY(tmpP.y() - 8);

          tmpP.setX(tabBarItem->x() + tabBarItem->width());
          tmpP.setY(tabBarItem->y() + tabBarItem->height());

          drawPRL.setX(tmpP.x() - 8);
          drawPRL.setY(tmpP.y() - 8);

          drawPRR.setX(tmpP.x() + 8);
          drawPRR.setY(tmpP.y() - 8);

          LOG_DEBUG << "drawPLL:" << drawPLL;
          LOG_DEBUG << "drawPLR:" << drawPLR;
          LOG_DEBUG << "drawPRL:" << drawPRL;
          LOG_DEBUG << "drawPRR:" << drawPRR;
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

      void resizeEvent(QResizeEvent* event)
      {
          // LOG_DEBUG << "width:" << width();
          QScrollArea::resizeEvent(event);
         // adjustTabBarItemSize();
      }

      void paintEvent(QPaintEvent* event)
      {
          QScrollArea::paintEvent(event);

          QPoint  drawPLL;
          QPoint  drawPLR;
          QPoint  drawPRL;
          QPoint  drawPRR;
          getDrawCenterPoint(drawPLL, drawPLR, drawPRL, drawPRR);

          //QPainter painter(viewport());
          //painter.setPen(QPen(Qt::blue, 1));
          //painter.setBrush(Qt::yellow);
          //painter.drawEllipse(20, 20, 50, 50);
      }
  protected:
      QWidget* m_hMainWidget;
      QHBoxLayout* m_hMainLayout;
      QHBoxLayout* m_hLeftLayout;
      QHBoxLayout* m_hMidLayout;
      QHBoxLayout* m_hRightLayout;

      QPushButton* m_addTabBtn;

      int m_nTabBarItemMaxWidth;
      int m_nTabBarItemMinWidth;

      QPoint m_dragPoint;
      bool m_bDraging;
      std::vector<FluTabBarItem*> m_tabBarItems;
};
