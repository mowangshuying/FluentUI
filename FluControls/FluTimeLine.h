#pragma once

#include "FluWidget.h"
#include "FluVScrollView.h"
#include "FluTimeLineItem.h"
#include <QPainter>

class FluTimeLine : public FluVScrollView
{
    Q_OBJECT
  public:
      FluTimeLine(QWidget* parent = nullptr) : FluVScrollView(parent)
      {
          m_vMainLayout->setSpacing(0);
          m_vMainLayout->setAlignment(Qt::AlignTop);
      }

      void addTimeLineItem(QString text)
      {
          addTimeLineItem(-1, text);
      }

      void addTimeLineItem(int nIndex, QString text)
      {
          if (nIndex == -1)
          {
              if (m_itemsMap.empty())
              {
                  nIndex = 0;
              }
              else
              {
                  auto iter = m_itemsMap.rbegin();
                  nIndex = iter->first + 1;
              }

              auto timeLineItem = new FluTimeLineItem;
              timeLineItem->addTextItem(text);
              m_itemsMap[nIndex] = timeLineItem;
              m_vMainLayout->addWidget(timeLineItem, 0,  Qt::AlignTop);
              return;
          }
          else
          {
              auto itf = m_itemsMap.find(nIndex);
              if (itf != m_itemsMap.end())
              {
                  itf->second->addTextItem(text);
              }
          }
      }

      //void paintEvent(QPaintEvent* event)
      //{
      //    FluVScrollView::paintEvent(event);
      //
      //}

      //void resizeEvent(QResizeEvent* event)
      //{

      //}

 protected:
      std::map<int, FluTimeLineItem*> m_itemsMap;
};
