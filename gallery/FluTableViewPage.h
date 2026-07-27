#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluTableView.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"

class FluTableViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluTableViewPage(QWidget* parent = nullptr);
  public slots:
    void onThemeChanged();
};
