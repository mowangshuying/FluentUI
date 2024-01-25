#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDropDownButton.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluDropDownButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluDropDownButtonPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("DropDownButton");
        m_infoLabel->setText("A control that drops down a flyout of chices from which one can be chosen.");
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDropDownButtonPage.qss", this);

        auto displayBox1 = new FluDisplayBox;
        displayBox1->setTitle("Simple DropDownButton");
        displayBox1->getCodeExpander()->setCodeByPath("../code/DropDownButtonCode1");
        displayBox1->setBodyWidgetFixedHeight(96);

        auto dropDownButton1 = new FluDropDownButton(this);
        dropDownButton1->setFixedWidth(78);
        dropDownButton1->setText("Email");
        dropDownButton1->addTextItem("Send");
        dropDownButton1->addTextItem("Reply");
        dropDownButton1->addTextItem("Reply All");

        displayBox1->getBodyLayout()->addWidget(dropDownButton1);
        m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);
    }
};
