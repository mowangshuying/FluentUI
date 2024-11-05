#include "FluCalendarDatePickerPage.h"

FluCalendarDatePickerPage::FluCalendarDatePickerPage(QWidget* parent /*= nullptr*/)
{
    m_mainLayout->setAlignment(Qt::AlignTop);

    m_titleLabel->setText("CalendarDatePicker");
    m_infoLabel->setText("A control that lets users pick a date value using a calendar.");

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle("CalendarDatePicker with a header ad placeholder text.");
    displayBox->getCodeExpander()->setCodeByPath("../code/CalendarDatePickerPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(60);

    auto calendarView = new FluCalendarDatePicker(displayBox);
    calendarView->move(50, 50);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarDatePickerPage.qss", this);
}

void FluCalendarDatePickerPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarDatePickerPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCalendarDatePickerPage.qss", this);
    }
}
