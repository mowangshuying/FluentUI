#pragma once

#include "FluWidget.h"
#include "FluTeachingTip.h"

class FluTeachingTipContent : public FluWidget
{
    Q_OBJECT
  public:
    FluTeachingTipContent(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

  protected:
    QColor m_borderC;
    QColor m_brushC;

    FluTeachingTipPosition m_TipPos;

    int m_nSpacing;
};
