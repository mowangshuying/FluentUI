#pragma once

#include "FluWidget.h"
#include "FluTeachingTip.h"

class FluTeachingTipContent : public FluWidget
{
    Q_OBJECT
  public:
    FluTeachingTipContent(QWidget* parent = nullptr) : FluWidget(parent)
    {
    }

    void paintEvent(QPaintEvent* event)
    {
        FluWidget::paintEvent(event);
    }

  protected:
    QColor m_borderC;
    QColor m_brushC;

    FluTeachingTipPos m_TipPos;

    int m_nSpacing;
};
