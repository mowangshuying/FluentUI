#pragma once

#include "FluAEmptyPage.h"
#include "FluATitlePage.h"
#include "../controls/FluHCard.h"
#include "../controls/FluFWScrollView.h"
#include "../utils/FluUtils.h"

class FluMediaPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluMediaPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
