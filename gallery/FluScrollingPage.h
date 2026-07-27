#pragma once

#include "FluAEmptyPage.h"
#include "FluATitlePage.h"
#include "../Controls/FluHCard.h"
#include "../Controls/FluFWScrollView.h"

#include "../Utils/FluUtils.h"

class FluScrollingPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluScrollingPage(QWidget* parent = nullptr);
  signals:
    void clickedHCard(QString key);
  public slots:
    void onThemeChanged()
    {
        FluStyleSheetUtils::setQssByFileName("FluScrollingPage.qss", this, FluThemeUtils::getUtils()->getTheme());
    }
};
