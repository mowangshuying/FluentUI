#pragma once

#include "FluAEmptyPage.h"
#include "FluATitlePage.h"
#include "../controls/FluHCard.h"
#include "../controls/FluFWScrollView.h"

#include "../utils/FluUtils.h"

class FluNavigationPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluNavigationPage(QWidget* parent = nullptr);


  public slots:
    void onThemeChanged();
};
