#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluListView.h"

class FluListViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluListViewPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
