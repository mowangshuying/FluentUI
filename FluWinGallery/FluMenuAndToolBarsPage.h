#pragma once

#include "FluAEmptyPage.h"
#include "FluATitlePage.h"
#include "../FluControls/FluHCard.h"
#include "../FluControls/FluFWScrollView.h"

#include "../FluUtils/FluUtils.h"

class FluMenuAndToolBarsPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluMenuAndToolBarsPage(QWidget* parent = nullptr);
  signals:
    void clickedHCard(QString key);
  public slots:
    void onThemeChanged();
};
