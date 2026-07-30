#pragma once

#include "FluAEmptyPage.h"
#include "FluATitlePage.h"
#include "../controls/FluHCard.h"
#include "../controls/FluFWScrollView.h"

class FluStatusAndInfoPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluStatusAndInfoPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
