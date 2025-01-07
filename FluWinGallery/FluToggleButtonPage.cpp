#include "FluToggleButtonPage.h"

FluToggleButtonPage::FluToggleButtonPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("ToggleButton"));

    // m_subTitleLabel->setText("FluentUI::FluToggleButton");

    m_infoLabel->setText(tr("ToggleButton demos."));

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("A simple toggle button with text content."));
    displayBox1->getCodeExpander()->setCodeByPath("../code/ToggleButtonPageCode1.md");
    auto btn1 = new FluToggleButton(this);
    btn1->setText(tr("Toggle Button"));
    displayBox1->setBodyWidgetFixedHeight(96);
    displayBox1->getBodyLayout()->addWidget(btn1);
    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    onThemeChanged();
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
