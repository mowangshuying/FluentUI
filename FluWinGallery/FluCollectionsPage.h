#pragma once

#include "../FluControls/FluWidget.h"
#include <QLabel>
#include "../FluControls/FluFWScrollView.h"
#include "FluATitlePage.h"
#include "FluATitlePage.h"
#include "../FluControls/FluHCard.h"

class FluCollectionsPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluCollectionsPage(QWidget* parent = nullptr);

  signals:
    void clickedHCard(QString key);
  public slots:
    void onThemeChanged();
};
