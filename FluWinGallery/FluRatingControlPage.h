#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluRatingControl.h"

class FluRatingControlPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRatingControlPage(QWidget* parent = nullptr);
  public slots:
    void onThemeChanged();
};
