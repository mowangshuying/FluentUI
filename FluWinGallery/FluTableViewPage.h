#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluTableView.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluTableViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluTableViewPage(QWidget* parent = nullptr);
  public slots:
    void onThemeChanged();
};
