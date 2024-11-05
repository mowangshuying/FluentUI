#pragma once

#include "FluAEmptyPage.h"

#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluAutoSuggestBox.h"

class FluAutoSuggestBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluAutoSuggestBoxPage(QWidget* parent = nullptr);
  public slots:
    void onThemeChanged();
};
