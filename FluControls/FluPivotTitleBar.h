#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include "FluPivotTitleBarItem.h"

class FluPivotTitleBar : public QWidget
{
	Q_OBJECT
  public:
	  FluPivotTitleBar(QWidget* parent = nullptr) : QWidget(parent)
	  {
              m_hMainLayout = new QHBoxLayout;
              setLayout(m_hMainLayout);

			  m_hMainLayout->setContentsMargins(0, 0, 0, 0);
              m_hMainLayout->setAlignment(Qt::AlignLeft);
	  }

	  void addTitleBarItem(FluPivotTitleBarItem* item)
	  {
            m_hMainLayout->addWidget(item);
	  }

	  void setCurTitleBarItem(FluPivotTitleBarItem* titleBarItem)
	  {
		  for (int i = 0; i < m_hMainLayout->count(); i++)
		  {
                      QLayoutItem* item = m_hMainLayout->itemAt(i);
                      if (item == nullptr)
                          continue;

					  FluPivotTitleBarItem* curTitleBarItem = (FluPivotTitleBarItem*)item->widget();
                      if (curTitleBarItem == nullptr)
						  continue;

					  if (titleBarItem == curTitleBarItem)
					  {
                          curTitleBarItem->setSelected(true);
					  }
					  else
					  {
                          curTitleBarItem->setSelected(false);
					  }
		  }
	  }

  protected:
      QHBoxLayout* m_hMainLayout;
};
