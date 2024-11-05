#include "FluToggleSwitchPage.h"

FluToggleSwitchPage::FluToggleSwitchPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("ToggleSwith");
    m_infoLabel->setText("Use ToggleSwith controls to present users with exactly two mutually exclusive options(lik on/off), where choosing an option results in an immediate commit. A toggle switch should have a single label.");

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle("A simple ToggleSwitch.");
    displayBox->getCodeExpander()->setCodeByPath("../code/ToggleSwitchPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(70);

    auto toggleSwitch = new FluTextToggleSwitchEx(displayBox);
    toggleSwitch->move(50, 50);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluToggleSwitchPage.qss", this);
}

void FluToggleSwitchPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluToggleSwitchPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluToggleSwitchPage.qss", this);
    }
}
