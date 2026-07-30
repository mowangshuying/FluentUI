#pragma once

#include "FluATitlePage.h"
#include "../controls/FluHCard.h"
#include "../controls/FluFWScrollView.h"

class FluTextPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluTextPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
