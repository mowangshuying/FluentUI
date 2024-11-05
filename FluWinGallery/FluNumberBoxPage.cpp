#include "FluNumberBoxPage.h"

FluNumberBoxPage::FluNumberBoxPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("NumberBox");

    m_infoLabel->setText("Use NumberBox to allow users to enter a algebraic equations and numeric input in your app.");

    addSpinBox();

    addDoubleSpinBox();

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNumberBoxPage.qss", this);
}

void FluNumberBoxPage::addSpinBox()
{
    auto displayBox = new FluDisplayBox;
    displayBox->setTitle("A spin box");
    displayBox->getCodeExpander()->setCodeByPath("../code/NumberBoxPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(90);

    auto spinBox = new FluSpinBox(this);
    spinBox->setFixedWidth(150);
    displayBox->getBodyLayout()->addWidget(spinBox);
    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluNumberBoxPage::addDoubleSpinBox()
{
    auto displayBox = new FluDisplayBox;
    displayBox->setTitle("A double spin box");
    displayBox->getCodeExpander()->setCodeByPath("../code/NumberBoxPageCode2.md");
    displayBox->setBodyWidgetFixedHeight(90);

    auto doubleSpinBox = new FluDoubleSpinBox(this);
    doubleSpinBox->setFixedWidth(150);
    displayBox->getBodyLayout()->addWidget(doubleSpinBox);
    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluNumberBoxPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNumberBoxPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluNumberBoxPage.qss", this);
    }
}
