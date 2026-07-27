#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluPasswordBox.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"

class FluPasswordBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluPasswordBoxPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
