#pragma once

#include "FluWidget.h"
#include "FluVScrollView.h"
#include "FluTimeLineItem.h"
#include <QPainter>

class FluTimeLine : public FluVScrollView
{
    Q_OBJECT
  public:
    FluTimeLine(QWidget* parent = nullptr);

    void addTimeLineItem(QString text);

    void addTimeLineItem(int nIndex, QString text);

    // void paintEvent(QPaintEvent* event)
    //{
    //     FluVScrollView::paintEvent(event);
    //
    // }

    // void resizeEvent(QResizeEvent* event)
    //{

    //}

  protected:
    std::map<int, FluTimeLineItem*> m_itemsMap;
};
