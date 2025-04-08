#pragma once

#include <QPushButton>
#include "../FluUtils/FluUtils.h"

class FluSegmentedItem : public QPushButton
{
	Q_OBJECT
  public:
	  FluSegmentedItem(QWidget* parent = nullptr) : QPushButton(parent)
	  {
            setFixedHeight(30);
            onThemeChanged();

            connect(this, &FluSegmentedItem::clicked, this, [=]() { 
                emit ItemClicked(this);
            });
      }
   signals:
      void ItemClicked(FluSegmentedItem* item);
   public slots:
	   void onThemeChanged()
	   {
            if (FluThemeUtils::isLightTheme())
            {
                FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSegmentedItem.qss", this);
            }
            else if (FluThemeUtils::isDarkTheme())
            {
                FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluSegmentedItem.qss", this);
            }
	   }

	protected:
};
