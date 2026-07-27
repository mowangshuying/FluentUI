#pragma once

#include "../controls/FluCalendarView.h"
#include "FluAEmptyPage.h"
#include "../controls/FluDisplayBox.h"
#include "../controls/FluVScrollView.h"

class FluCalendarViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluCalendarViewPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
