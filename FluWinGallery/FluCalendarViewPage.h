#pragma once

#include "../FluControls/FluCalendarView.h"
#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluCalendarViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluCalendarViewPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
