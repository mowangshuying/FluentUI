#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluCalendarDatePicker.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluVScrollView.h"

class FluCalendarDatePickerPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluCalendarDatePickerPage(QWidget* parent = nullptr)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);

        m_titleLabel->setText("CalendarDatePickerPage");
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

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarDatePickerPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCalendarDatePickerPage.qss", this);
        }
    }
};
