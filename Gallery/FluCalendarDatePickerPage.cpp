#include "FluCalendarDatePickerPage.h"

FluCalendarDatePickerPage::FluCalendarDatePickerPage(QWidget* parent /*= nullptr*/)
{
    m_mainLayout->setAlignment(Qt::AlignTop);

    m_titleLabel->setText(tr("CalendarDatePicker"));
    m_infoLabel->setText(tr("A control that lets users pick a date value using a calendar."));

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("CalendarDatePicker with a header ad placeholder text."));
    displayBox->getCodeExpander()->setCodeByPath("../code/CalendarDatePickerPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(60);

    auto calendarView = new FluCalendarDatePicker(displayBox);
    calendarView->move(50, 50);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    onThemeChanged();
}

void FluCalendarDatePickerPage::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluCalendarDatePickerPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
