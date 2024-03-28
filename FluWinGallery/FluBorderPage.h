#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluBorder.h"
#include "../FluControls/FluDisplayBoxEx.h"
#include "../FluControls/FluVRadioGroupBox.h"

class FluBorderPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluBorderPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("Border");
        m_infoLabel->setText("Use a Border control to draw a boundary line, background or both, around another object. A Border can contain only one child object");

        auto displayBox = new FluDisplayBoxEx;
        displayBox->setTitle("A Border around a TextBlock.");
        displayBox->getCodeExpander()->setCodeByPath("../code/BorderPageCode1.md");
        displayBox->setBodyWidgetFixedHeight(120);

        auto boder = new FluBorder;
        boder->setFixedSize(250, 40);
        boder->setText("Text inside a border");
        displayBox->getBodyContentLayout()->addWidget(boder);

        FluVRadioGroupBox* group = new FluVRadioGroupBox("Background", this);
        auto btn1 = new FluRadioButton("Green", group);
        auto btn2 = new FluRadioButton("Yellow", group);
        auto btn3 = new FluRadioButton("Blue", group);
        group->addRadioButton(btn1);
        group->addRadioButton(btn2);
        group->addRadioButton(btn3);
        connect(btn1, &FluRadioButton::toggled, [=]() { boder->setBackGroundColor("green"); });
        connect(btn2, &FluRadioButton::toggled, [=]() { boder->setBackGroundColor("yellow"); });
        connect(btn3, &FluRadioButton::toggled, [=]() { boder->setBackGroundColor("blue"); });

        displayBox->getBodyRightLayout()->addWidget(group);

        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluBorderPage.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluBorderPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluBorderPage.qss", this);
        }
    }
};
