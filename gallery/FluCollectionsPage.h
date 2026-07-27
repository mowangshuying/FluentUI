#pragma once

#include "../Controls/FluWidget.h"
#include <QLabel>
#include "../Controls/FluFWScrollView.h"
#include "FluATitlePage.h"
#include "FluATitlePage.h"
#include "../Controls/FluHCard.h"

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
