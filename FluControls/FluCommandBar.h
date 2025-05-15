#pragma once

#include <QFrame>
#include "../FluUtils/FluUtils.h"
#include <vector>
#include "FluCommandBarItem.h"

class FluCommandBar : public QFrame 
{
	Q_OBJECT
  public:
	  FluCommandBar(QWidget* parent = nullptr) : QFrame(parent)
	  {

	  }

	  void insertBarItem(int nIndex, FluCommandBarItem* barItem)
	  {
            barItem->setParent(this);
            barItem->show();

			if (nIndex < 0 || nIndex >= m_widgets.size())
			{
                m_widgets.push_back(barItem);
			}
			else
			{
                m_widgets.insert(m_widgets.begin() + nIndex, barItem);
			}
	  }

	  void addBarItem(FluCommandBarItem* barItem)
	  {

	  }
   public slots:
   protected:
     std::vector<FluCommandBarItem*> m_widgets;
};
