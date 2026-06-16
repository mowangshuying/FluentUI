#pragma once

#include "FluAEmptyPage.h"
#include "FluATitlePage.h"
#include "../Controls/FluHCard.h"
#include "../Controls/FluFWScrollView.h"

class FluStatusAndInfoPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluStatusAndInfoPage(QWidget* parent = nullptr);
  signals:
    void clickedHCard(QString key);
  public slots:
    void onThemeChanged();
};
