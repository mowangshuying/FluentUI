#pragma once

#include "FluAEmptyPage.h"

class FluTreeViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluTreeViewPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
