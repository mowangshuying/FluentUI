#pragma once

#include <QScrollArea>
#include "FluScrollDelegate.h"
#include "FluScrollBar.h"

class FluScrollArea : public QScrollArea
{
    Q_OBJECT
  public:
      FluScrollArea(QWidget* parent = nullptr) : QScrollArea(parent)
      {
          m_scrollDelegate = new FluScrollDelegate(this);
      }


      void hideVScrollBar()
      {
          setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
          m_scrollDelegate->getVScrollBar()->hide();
      }

      void hideHScrollBar()
      {
          setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
          m_scrollDelegate->getHScrollBar()->hide();
      }
    protected:
        FluScrollDelegate* m_scrollDelegate = nullptr;
};
