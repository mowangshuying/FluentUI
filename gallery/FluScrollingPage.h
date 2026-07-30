#pragma once

#include "FluAEmptyPage.h"
#include "FluATitlePage.h"
#include "../controls/FluHCard.h"
#include "../controls/FluFWScrollView.h"

#include "../utils/FluUtils.h"

class FluScrollingPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluScrollingPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged()
    {
        FluStyleSheetUtils::setQssByFileName("FluScrollingPage.qss", this, FluThemeUtils::getUtils()->getTheme());
    }
};
