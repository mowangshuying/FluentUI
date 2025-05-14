#pragma once

#include "FluWidget.h"
#include "FluCommandBarItemType.h"

class FluCommandBarItem : public FluWidget
{
	Q_OBJECT
  public:
	  FluCommandBarItem(FluCommandBarItemType type, QWidget* parent = nullptr)
	  {
            m_itemType = type;
	  }

signals:
	 
public slots:
  protected:
      FluCommandBarItemType m_itemType;
};
