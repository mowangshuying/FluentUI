#pragma once

#include "FluAEmptyPage.h"
#include "FluATitlePage.h"
#include "../controls/FluHCard.h"
#include "../controls/FluFWScrollView.h"

#include "../utils/FluUtils.h"

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
