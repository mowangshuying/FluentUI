#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluCalendarView.h"
#include "../FluControls/FluCalendarDef.h"

class FluCalendarViewDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluCalendarViewDemo(QWidget* parent = nullptr) : FluWidget(parent)
    {
        auto calendarView = new FluCalendarView(this);
        calendarView->move(50, 50);
        resize(600, 600);
    }
};
