#pragma once

#include "../FluControls/FluCalendarDatePicker.h"
#include "FluTemplateDemo.h"

class FluCalendarDatePickerDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluCalendarDatePickerDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
    {
        FluCalendarDatePicker* picker = new FluCalendarDatePicker(this);
        picker->move(50, 50);

        resize(600, 400);
    }
};
