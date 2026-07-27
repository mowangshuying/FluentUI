#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluPasswordBox.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"

class FluPasswordBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluPasswordBoxPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
