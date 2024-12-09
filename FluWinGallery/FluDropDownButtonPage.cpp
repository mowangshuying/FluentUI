#include "FluDropDownButtonPage.h"

FluDropDownButtonPage::FluDropDownButtonPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("DropDownButton");
    // m_subTitleLabel->setText("FluentUI::FluDropDownButton");
    m_infoLabel->setText("A control that drops down a flyout of chices from which one can be chosen.");
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDropDownButtonPage.qss", this);

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle("Simple DropDownButton");
    displayBox1->getCodeExpander()->setCodeByPath("../code/DropDownButtonPageCode1.md");
    displayBox1->setBodyWidgetFixedHeight(56);

    auto dropDownButton1 = new FluDropDownButton(this);
    dropDownButton1->setFixedWidth(78);
    dropDownButton1->setText("Email");
    dropDownButton1->addTextItem("Send");
    dropDownButton1->addTextItem("Reply");
    dropDownButton1->addTextItem("Reply All");

    displayBox1->getBodyLayout()->addWidget(dropDownButton1);
    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    auto displayBox2 = new FluDisplayBox;
    displayBox2->setTitle("DropDownButton with Icons");
    displayBox2->getCodeExpander()->setCodeByPath("../code/DropDownButtonPageCode2.md");
    displayBox2->setBodyWidgetFixedHeight(56);

    auto dropDownButton2 = new FluDropDownButton(this);
    dropDownButton2->setFixedWidth(78);
    dropDownButton2->setIcon(FluAwesomeType::Mail);
    dropDownButton2->addIconTextItem(FluAwesomeType::Send, "Send");
    dropDownButton2->addIconTextItem(FluAwesomeType::MailReply, "Reply");
    dropDownButton2->addIconTextItem(FluAwesomeType::MailReplyAll, "Reply All");

    displayBox2->getBodyLayout()->addWidget(dropDownButton2);
    m_vScrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);
}

void FluDropDownButtonPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDropDownButtonPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluDropDownButtonPage.qss", this);
    }
}
