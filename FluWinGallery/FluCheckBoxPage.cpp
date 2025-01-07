#include "FluCheckBoxPage.h"

FluCheckBoxPage::FluCheckBoxPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("CheckBox"));

    //   m_subTitleLabel->setText("FluentUI::FluCheckBox");

    m_infoLabel->setText(
        tr("CheckBox controls let the user select a combination of binary options.In contrast, RadioButton controls allow the user to select from mutually exclusive options.The indeterminate state is used to indicate that an option is set for "
           "some,but not all,child options. Don't allow users to set an indeterminate state directly to indicate a third option."));

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("A 2-state CheckBox"));
    displayBox1->getCodeExpander()->setCodeByPath("../code/CheckBoxPageCode1.md");
    displayBox1->setBodyWidgetFixedHeight(56);

    auto checkBox = new FluCheckBox(tr("Two-State CheckBox"), this);
    displayBox1->getBodyLayout()->addWidget(checkBox);
    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    auto displayBox2 = new FluDisplayBox;
    displayBox2->setTitle(tr("A 3-state CheckBox"));
    displayBox2->getCodeExpander()->setCodeByPath("../code/CheckBoxPageCode2.md");
    displayBox2->setBodyWidgetFixedHeight(56);

    auto checkBox2 = new FluCheckBox(tr("Three-state CheckBox"), this);
    checkBox2->setTristate(true);
    displayBox2->getBodyLayout()->addWidget(checkBox2);
    m_vScrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);

    onThemeChanged();
}

void FluCheckBoxPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCheckBoxPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCheckBoxPage.qss", this);
    }
}
