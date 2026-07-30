#include "FluDateAndTimePage.h"

FluDateAndTimePage::FluDateAndTimePage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_mainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText(tr("Date & Time"));

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/CalendarDatePicker.png")), tr("CalendarDatePicker"), tr("A control that lets users pick a date value using a calendar."), "CalendarDatePickerPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/CalendarView.png")), tr("CalendarView"), tr("A control that presents aa calendar for a user to choose a date from."), "CalendarViewPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/DatePicker.png")), tr("DatePicker"), tr("A control that lets a user pick a date value."), "DatePickerPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/TimePicker.png")), tr("TimePicker"), tr("A configurable control that lets a user pick a time value."), "TimePickerPage");

    onThemeChanged();
}

void FluDateAndTimePage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluDateAndTimePage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
