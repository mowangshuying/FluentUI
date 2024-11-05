#include "FluTimePickerPage.h"

FluTimePickerPage::FluTimePickerPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("TimePicker");
    m_infoLabel->setText(
        "Use a TimePicker to let users set a time in your app. for example to set a reminder. The TimePicker displays three controls"
        "for hour, minute, and AM/PM. These controls are easy to use with touch or mouse, and they can be styled and configured in several different ways.");

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle("A simple TimePicker");
    displayBox1->getCodeExpander()->setCodeByPath("../code/TimePickerPageCode1.md");
    auto timePickerAp = new FluTimePickerAP;
    displayBox1->getBodyLayout()->addWidget(timePickerAp);

    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    auto displayBox2 = new FluDisplayBox;
    displayBox2->setTitle("A TimePicker using a 24-hour clock.");
    displayBox2->getCodeExpander()->setCodeByPath("../code/TimePickerPageCode2.md");
    auto timePicker24H = new FluTimePicker24H;
    displayBox2->getBodyLayout()->addWidget(timePicker24H);
    m_vScrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTimePickerPage.qss", this);
}

void FluTimePickerPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTimePickerPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTimePickerPage.qss", this);
    }
}
