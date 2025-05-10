#pragma once

#include "FluAEmptyPage.h"

class FluColorPickerPage : public FluAEmptyPage
{
	Q_OBJECT
  public:
        FluColorPickerPage(QWidget* parent = nullptr);
	signals:
          void clickedHCard();
    public slots:
          void onThemeChanged();
};
