#pragma once

#include "../controls/FluWidget.h"
#include <QLabel>
#include "../controls/FluFWScrollView.h"
#include "FluATitlePage.h"
#include "FluATitlePage.h"
#include "../controls/FluHCard.h"

class FluCollectionsPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluCollectionsPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
