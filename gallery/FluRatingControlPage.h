#pragma once

#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluRatingControl.h"

class FluRatingControlPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRatingControlPage(QWidget* parent = nullptr);
  public slots:
    void onThemeChanged();
};
