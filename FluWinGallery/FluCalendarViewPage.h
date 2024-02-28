#pragma once

#include "../FluControls/FluCalendarView.h"
#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluCalendarViewPage : public FluAEmptyPage 
{
    Q_OBJECT
  public:
    FluCalendarViewPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("CalendarViewPage");
        m_subTitleLabel->setText("CppQtFluentUi888::FluCalendarView");
        m_infoLabel->setText("CalendarView shows a larger view for showing and selecting dates. DatePicker by contrast has a compact view with inline selection.");

        auto displayBox = new FluDisplayBox;
        displayBox->setTitle("A basic calendar view.");
        displayBox->getCodeExpander()->setCodeByPath("../code/FluCalendarViewPageCode1");
        displayBox->setBodyWidgetFixedHeight(400);

        auto calendarView = new FluCalendarView(displayBox);
        calendarView->move(50, 50);

        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewPage.qss", this);

    }
};
