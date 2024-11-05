#include "FluCalendarViewPage.h"

FluCalendarViewPage::FluCalendarViewPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("CalendarView");
    // m_subTitleLabel->setText("CppQtFluentUi888.FluControls.FluCalendarView");
    m_infoLabel->setText("CalendarView shows a larger view for showing and selecting dates. DatePicker by contrast has a compact view with inline selection.");

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle("A basic calendar view.");
    displayBox->getCodeExpander()->setCodeByPath("../code/CalendarViewPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(400);

    auto calendarView = new FluCalendarView(displayBox);
    calendarView->move(50, 50);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewPage.qss", this);
}

void FluCalendarViewPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCalendarViewPage.qss", this);
    }
}
