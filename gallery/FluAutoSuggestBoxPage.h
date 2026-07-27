#pragma once

#include "FluAEmptyPage.h"

#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluAutoSuggestBox.h"

class FluAutoSuggestBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluAutoSuggestBoxPage(QWidget* parent = nullptr);
  public slots:
    void onThemeChanged();
};
