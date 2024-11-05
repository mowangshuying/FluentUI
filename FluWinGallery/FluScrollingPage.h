#pragma once

#include "FluAEmptyPage.h"
#include "FluATitlePage.h"
#include "../FluControls/FluHCard.h"
#include "../FluControls/FluFWScrollView.h"

#include "../FluUtils/FluUtils.h"

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
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluScrollingPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluScrollingPage.qss", this);
        }
    }
};
