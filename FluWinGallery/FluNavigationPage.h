#pragma once

#include "FluAEmptyPage.h"
#include "FluATitlePage.h"
#include "../FluControls/FluHCard.h"
#include "../FluControls/FluFWScrollView.h"

#include "../FluUtils/FluUtils.h"

class FluNavigationPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluNavigationPage(QWidget* parent = nullptr);

  signals:
    void clickedHCard(QString key);
  public slots:
    void onThemeChanged();
};
