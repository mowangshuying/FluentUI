#include "FluCalendarViewDemo.h"

FluCalendarViewDemo::FluCalendarViewDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    auto calendarView = new FluCalendarView(this);
    calendarView->move(50, 50);
    resize(600, 600);
}
