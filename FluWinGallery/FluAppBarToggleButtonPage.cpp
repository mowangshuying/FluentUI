#include "FluAppBarToggleButtonPage.h"

FluAppBarToggleButtonPage::FluAppBarToggleButtonPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("AppBarToggleButton");
    m_infoLabel->setText(
        "An AppBarToggleButton looks like an AppBarButton, but works like a CheckBox. It typically has two state, checked(on) or unchecked(off), "
        "but can be indeterminate if the IsThreeState property is true. You can determine it's state by checking the IsChecked property.");

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAppBarToggleButtonPage.qss", this);

    addSymbolIconAppBarButton();
}

void FluAppBarToggleButtonPage::addSymbolIconAppBarButton()
{
    auto displayBox = new FluDisplayBox;
    displayBox->setTitle("An AppBarButton with a symbol icon.");
    displayBox->getCodeExpander()->setCodeByPath("../code/AppBarToggleButtonPageCode1.md");

    auto appBarButton = new FluAppBarToggleButton(FluAwesomeType::Like);
    appBarButton->setText("SymbolIcon");
    displayBox->getBodyLayout()->addWidget(appBarButton);
    connect(appBarButton, &FluAppBarToggleButton::clicked, [=]() { LOG_DEBUG << "called"; });

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluAppBarToggleButtonPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAppBarToggleButtonPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluAppBarToggleButtonPage.qss", this);
    }
}
