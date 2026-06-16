#pragma once

#include "../Controls/FluCalendarView.h"
#include "FluAEmptyPage.h"
#include "../Controls/FluDisplayBox.h"
#include "../Controls/FluVScrollView.h"

class FluCalendarViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluCalendarViewPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
