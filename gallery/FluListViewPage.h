#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluListView.h"

class FluListViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluListViewPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
