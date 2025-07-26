#pragma once

#include "FluWidget.h"
#include "FluCommandBarItemType.h"

class FluCommandBarItem : public FluWidget
{
    Q_OBJECT
  public:
    FluCommandBarItem(QWidget* parent = nullptr) : FluWidget(parent)
    {
    }

  signals:

  public slots:
    void onThemeChanged() override
    {
    }

  protected:
    FluCommandBarItemType m_itemType;
};
