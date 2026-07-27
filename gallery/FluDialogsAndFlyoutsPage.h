#pragma once

#include "FluAEmptyPage.h"
#include "FluATitlePage.h"
#include "../Controls/FluFWScrollView.h"
#include "../Controls/FluHCard.h"

class FluDialogsAndFlyoutsPage : public FluATitlePage
{
    Q_OBJECT
  public:
  public:
    FluDialogsAndFlyoutsPage(QWidget* parent = nullptr);

  signals:
    void clickedHCard(QString key);
  public slots:
    void onThemeChanged();
};
