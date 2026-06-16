
#pragma once

#include "FluAEmptyPage.h"
#include "FluATitlePage.h"
#include "../Controls/FluHCard.h"
#include "../Controls/FluFWScrollView.h"

#include "../Utils/FluUtils.h"

class FluLayoutPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluLayoutPage(QWidget* parent = nullptr);
  signals:
    void clickedHCard(QString key);
  public slots:
    void onThemeChanged();
};
