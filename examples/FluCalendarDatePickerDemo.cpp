#include "FluCalendarDatePickerDemo.h"

FluCalendarDatePickerDemo::FluCalendarDatePickerDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    FluCalendarDatePicker* picker = new FluCalendarDatePicker(this);
    picker->move(50, 50);

    resize(600, 400);
}
