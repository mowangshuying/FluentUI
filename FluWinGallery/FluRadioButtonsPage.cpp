#include "FluRadioButtonsPage.h"

FluRadioButtonsPage::FluRadioButtonsPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("RadioButtons"));
    m_infoLabel->setText(tr("A control that displays a group of mutually exclusive options with keyboarding and accessibility support."));

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("Two RadioButtons controls with strings as options."));
    displayBox->getCodeExpander()->setCodeByPath("../code/RadioButtonsPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(360);

    auto border = new FluBorder;
    border->setFixedSize(376, 54);
    border->setBorderWidth(12);

    auto* backgroundGroup = new FluHRadioGroupBox(tr("Background"), this);
    auto btn1 = new FluRadioButton(tr("Green"), backgroundGroup);
    auto btn2 = new FluRadioButton(tr("Yellow"), backgroundGroup);
    auto btn3 = new FluRadioButton(tr("White"), backgroundGroup);
    backgroundGroup->addRadioButton(btn1);
    backgroundGroup->addRadioButton(btn2);
    backgroundGroup->addRadioButton(btn3);
    connect(btn1, &FluRadioButton::toggled, [=]() { border->setBackGroundColor("green"); });
    connect(btn2, &FluRadioButton::toggled, [=]() { border->setBackGroundColor("yellow"); });
    connect(btn3, &FluRadioButton::toggled, [=]() { border->setBackGroundColor("white"); });

    auto* borderGroup = new FluHRadioGroupBox(tr("Border"), this);
    auto btn4 = new FluRadioButton(tr("Green"), borderGroup);
    auto btn5 = new FluRadioButton(tr("Yellow"), borderGroup);
    auto btn6 = new FluRadioButton(tr("White"), borderGroup);
    borderGroup->addRadioButton(btn4);
    borderGroup->addRadioButton(btn5);
    borderGroup->addRadioButton(btn6);
    connect(btn4, &FluRadioButton::toggled, [=]() { border->setBorderColor("green"); });
    connect(btn5, &FluRadioButton::toggled, [=]() { border->setBorderColor("yellow"); });
    connect(btn6, &FluRadioButton::toggled, [=]() { border->setBorderColor("white"); });

    displayBox->getBodyLayout()->addWidget(backgroundGroup, Qt::AlignTop);
    displayBox->getBodyLayout()->addWidget(borderGroup, Qt::AlignTop);
    displayBox->getBodyLayout()->addWidget(border, Qt::AlignTop);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    onThemeChanged();
}

void FluRadioButtonsPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluRadioButtonsPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluRadioButtonsPage.qss", this);
    }
}
