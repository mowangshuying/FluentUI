#include "FluTimePickerDemo.h"

FluTimePickerDemo::FluTimePickerDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    setWindowTitle("Date & Time Picker Demo");
#ifdef _DEBUG
    setWindowTitle("Date & Time Picker Demo Dev");
#endif
    auto timePicker24H = new FluTimePicker24H(this);
    timePicker24H->move(300 - timePicker24H->width() / 2, 100);

    auto timePickerAP = new FluTimePickerAP(this);
    timePickerAP->move(300 - timePickerAP->width() / 2, 200);

    auto datePicker = new FluDatePicker(this);
    datePicker->move(300 - datePicker->width() / 2, 300);
    resize(600, 600);
}
