#include "FluToggleButtonPage.h"

FluToggleButtonPage::FluToggleButtonPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("ToggleButton");

    // m_subTitleLabel->setText("CppQtFluentUi888::FluToggleButton");

    m_infoLabel->setText("ToggleButton demos.");

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle("A simple toggle button with text content.");
    displayBox1->getCodeExpander()->setCodeByPath("../code/ToggleButtonPageCode1.md");
    auto btn1 = new FluToggleButton(this);
    btn1->setText("Toggle Button");
    displayBox1->setBodyWidgetFixedHeight(96);
    displayBox1->getBodyLayout()->addWidget(btn1);
    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluToggleButtonPage.qss", this);
}

void FluToggleButtonPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluToggleButtonPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluToggleButtonPage.qss", this);
    }
}
