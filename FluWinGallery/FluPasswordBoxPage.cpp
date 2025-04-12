#include "FluPasswordBoxPage.h"

FluPasswordBoxPage::FluPasswordBoxPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("PasswordBox"));
    m_infoLabel->setText(
        tr("A user can enter a single line of non-wrapping text in a PasswordBox control. The text is Masked by characters that you can specify by using the PasswordChar property, and you can specify the maximum number of characters that the user "
           "can enter by setting the MaxLength property."));

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("A simple PasswordBox."));
    displayBox1->getCodeExpander()->setCodeByPath(FLURC("code/PasswordBoxPageCode1.md"));

    auto passwordBox1 = new FluPasswordBox(this);
    passwordBox1->setFixedWidth(240);
    displayBox1->setBodyWidgetFixedHeight(96);
    displayBox1->getBodyLayout()->addWidget(passwordBox1);
    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    // maskC
    auto displayBox2 = new FluDisplayBox;
    displayBox2->setTitle(tr("A PasswordBox with header, placeholder text and custom character."));
    displayBox2->getCodeExpander()->setCodeByPath(FLURC("code/PasswordBoxPageCode2.md"));

    auto passwordBox2 = new FluPasswordBox(this);
    passwordBox2->setMaskC(0x2a);
    passwordBox2->setFixedWidth(240);
    displayBox2->setBodyWidgetFixedHeight(96);
    displayBox2->getBodyLayout()->addWidget(passwordBox2);
    m_vScrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);

    onThemeChanged();
}

void FluPasswordBoxPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluPasswordBoxPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluPasswordBoxPage.qss"), this);
    }
}
