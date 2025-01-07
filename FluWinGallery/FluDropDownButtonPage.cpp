#include "FluDropDownButtonPage.h"

FluDropDownButtonPage::FluDropDownButtonPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("DropDownButton"));
    // m_subTitleLabel->setText("FluentUI::FluDropDownButton");
    m_infoLabel->setText(tr("A control that drops down a flyout of chices from which one can be chosen."));

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("Simple DropDownButton"));
    displayBox1->getCodeExpander()->setCodeByPath("../code/DropDownButtonPageCode1.md");
    displayBox1->setBodyWidgetFixedHeight(56);

    auto dropDownButton1 = new FluDropDownButton(this);
    dropDownButton1->setFixedWidth(78);
    dropDownButton1->setText(tr("Email"));
    dropDownButton1->addTextItem(tr("Send"));
    dropDownButton1->addTextItem(tr("Reply"));
    dropDownButton1->addTextItem(tr("Reply All"));

    displayBox1->getBodyLayout()->addWidget(dropDownButton1);
    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    auto displayBox2 = new FluDisplayBox;
    displayBox2->setTitle(tr("DropDownButton with Icons"));
    displayBox2->getCodeExpander()->setCodeByPath("../code/DropDownButtonPageCode2.md");
    displayBox2->setBodyWidgetFixedHeight(56);

    auto dropDownButton2 = new FluDropDownButton(this);
    dropDownButton2->setFixedWidth(78);
    dropDownButton2->setIcon(FluAwesomeType::Mail);
    dropDownButton2->addIconTextItem(FluAwesomeType::Send, tr("Send"));
    dropDownButton2->addIconTextItem(FluAwesomeType::MailReply, tr("Reply"));
    dropDownButton2->addIconTextItem(FluAwesomeType::MailReplyAll, tr("Reply All"));

    displayBox2->getBodyLayout()->addWidget(dropDownButton2);
    m_vScrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);

    onThemeChanged();
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
