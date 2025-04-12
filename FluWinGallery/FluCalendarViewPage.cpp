#include "FluCalendarViewPage.h"

FluCalendarViewPage::FluCalendarViewPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("CalendarView"));
    // m_subTitleLabel->setText("FluentUI.FluControls.FluCalendarView");
    m_infoLabel->setText(tr("CalendarView shows a larger view for showing and selecting dates. DatePicker by contrast has a compact view with inline selection."));

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("A basic calendar view."));
    displayBox->getCodeExpander()->setCodeByPath(FLURC("code/CalendarViewPageCode1.md"));
    displayBox->setBodyWidgetFixedHeight(400);

    auto calendarView = new FluCalendarView(displayBox);
    calendarView->move(50, 50);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    onThemeChanged();
}

void FluCalendarViewPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluCalendarViewPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluCalendarViewPage.qss"), this);
    }
}
