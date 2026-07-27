#pragma once

#include "FluATitlePage.h"
#include "../controls/FluHCard.h"
#include "../controls/FluFWScrollView.h"

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
