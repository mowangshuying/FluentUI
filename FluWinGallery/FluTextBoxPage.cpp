#include "FluTextBoxPage.h"

FluTextBoxPage::FluTextBoxPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("TextBox"));
    m_infoLabel->setText(tr("Use a TextBox to let a user enter simple text input in your app. You can add a header and placeholder text to let the user know what the TextBox is for,and you can customize it in other way."));
    FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluTextBoxPage.qss"), this);

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("A multi-line TextBox"));
    displayBox1->getCodeExpander()->setCodeByPath(FLURC("code/TextBoxPageCode1.md"));

    auto textEdit = new FluTextEdit;
    textEdit->setFixedWidth(300);
    textEdit->move(50, 50);
    textEdit->setAutoAdjustSize(true);

    displayBox1->getBodyLayout()->addWidget(textEdit);
    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluTextBoxPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluTextBoxPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluTextBoxPage.qss"), this);
    }
}
