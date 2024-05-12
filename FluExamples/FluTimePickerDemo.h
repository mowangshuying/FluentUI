#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluTimePicker24H.h"

#include "../FluControls/FluTimePickerAP.h"

#include "../FluControls/FluDatePicker.h"

class FluTimePickerDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluTimePickerDemo(QWidget* parent = nullptr) : FluWidget(parent)
    {
        //   auto timePicker24H = new FluTimePicker24H(this);
        //   timePicker24H->move(300 - timePicker24H->width() / 2, 200 - timePicker24H->height() / 2);

        //   auto timePickerAP = new FluTimePickerAP(this);
        //   timePickerAP->move(300 - timePickerAP->width() / 2, 200 - timePickerAP->height() / 2);

        auto datePicker = new FluDatePicker(this);
        datePicker->move(300 - datePicker->width() / 2, 200 - datePicker->height() / 2);
        resize(600, 400);
    }

  protected:
};
