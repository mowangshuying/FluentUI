#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluTableView.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"

class FluTableViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluTableViewPage(QWidget* parent = nullptr);
  public slots:
    void onThemeChanged();
};
