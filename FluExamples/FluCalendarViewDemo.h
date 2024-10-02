#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluCalendarView.h"
#include "../FluControls/FluCalendarDef.h"
#include "FluTemplateDemo.h"

class FluCalendarViewDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluCalendarViewDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
    {
        auto calendarView = new FluCalendarView(this);
        calendarView->move(50, 50);
        resize(600, 600);
    }
};
