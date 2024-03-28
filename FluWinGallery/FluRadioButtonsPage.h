#pragma once

#include "../FluControls/FluHRadioGroupBox.h"
#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluBorder.h"

class FluRadioButtonsPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRadioButtonsPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("RadioButtons");
        m_infoLabel->setText("A control that displays a group of mutually exclusive options with keyboarding and accessibility support.");

        auto displayBox = new FluDisplayBox;
        displayBox->setTitle("Two RadioButtons controls with strings as options.");
        displayBox->getCodeExpander()->setCodeByPath("../code/RadioButtonsPageCode1.md");
        displayBox->setBodyWidgetFixedHeight(360);

        auto border = new FluBorder;
        border->setFixedSize(376, 54);
        border->setBorderWidth(12);

        auto* backgroundGroup = new FluHRadioGroupBox("Background", this);
        auto btn1 = new FluRadioButton("Green", backgroundGroup);
        auto btn2 = new FluRadioButton("Yellow", backgroundGroup);
        auto btn3 = new FluRadioButton("White", backgroundGroup);
        backgroundGroup->addRadioButton(btn1);
        backgroundGroup->addRadioButton(btn2);
        backgroundGroup->addRadioButton(btn3);
        connect(btn1, &FluRadioButton::toggled, [=]() { border->setBackGroundColor("green"); });
        connect(btn2, &FluRadioButton::toggled, [=]() { border->setBackGroundColor("yellow"); });
        connect(btn3, &FluRadioButton::toggled, [=]() { border->setBackGroundColor("white"); });

        auto* borderGroup = new FluHRadioGroupBox("Border", this);
        auto btn4 = new FluRadioButton("Green", borderGroup);
        auto btn5 = new FluRadioButton("Yellow", borderGroup);
        auto btn6 = new FluRadioButton("White", borderGroup);
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
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluRadioButtonsPage.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluRadioButtonsPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluRadioButtonsPage.qss", this);
        }
    }
};
