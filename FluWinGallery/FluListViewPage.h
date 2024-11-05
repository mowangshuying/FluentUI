#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluListView.h"

class FluListViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluListViewPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
