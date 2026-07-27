#pragma once

#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluRatingControl.h"

class FluRatingControlPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRatingControlPage(QWidget* parent = nullptr);
  public slots:
    void onThemeChanged();
};
