#pragma once

#include "FluAEmptyPage.h"

#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluAutoSuggestBox.h"

class FluAutoSuggestBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluAutoSuggestBoxPage(QWidget* parent = nullptr);
  public slots:
    void onThemeChanged();
};
