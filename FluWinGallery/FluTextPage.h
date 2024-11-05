#pragma once

#include "FluATitlePage.h"
#include "../FluControls/FluHCard.h"
#include "../FluControls/FluFWScrollView.h"

class FluTextPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluTextPage(QWidget* parent = nullptr);
  signals:
    void clickedHCard(QString key);
  public slots:
    void onThemeChanged();
};
