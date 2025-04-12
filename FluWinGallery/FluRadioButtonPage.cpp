#include "FluRadioButtonPage.h"

FluRadioButtonPage::FluRadioButtonPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("RadioButton"));

    m_infoLabel->setText(tr("Use RadioButton to let a user choose between mutually exclusive, related options. Generally contained within a RadioButtons group control."));

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("A group of RadioButton controls in RadioButtons group."));
    displayBox->getCodeExpander()->setCodeByPath(FLURC("code/RadioButtonPageCode1.md"));
    displayBox->setBodyWidgetFixedHeight(160);

    FluVRadioGroupBox* groupBox = new FluVRadioGroupBox(tr("Options"));
    groupBox->move(50, 50);

    auto btn1 = new FluRadioButton(tr("Option 1"), groupBox);
    auto btn2 = new FluRadioButton(tr("Option 2"), groupBox);
    auto btn3 = new FluRadioButton(tr("Option 3"), groupBox);

    groupBox->addRadioButton(btn1);
    groupBox->addRadioButton(btn2);
    groupBox->addRadioButton(btn3);

    displayBox->getBodyLayout()->addWidget(groupBox);
    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);

    onThemeChanged();
}

void FluRadioButtonPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluRadioButtonPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluRadioButtonPage.qss"), this);
    }
}
