#pragma once

#include <QScrollArea>
#include "FluScrollDelegate.h"
#include "FluScrollBar.h"

class FluScrollArea : public QScrollArea
{
    Q_OBJECT
  public:
    FluScrollArea(QWidget* parent = nullptr);

    void hideVScrollBar();

    void hideHScrollBar();

  protected:
    FluScrollDelegate* m_scrollDelegate = nullptr;
};
