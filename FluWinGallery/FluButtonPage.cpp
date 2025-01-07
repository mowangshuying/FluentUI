#include "FluButtonPage.h"

FluButtonPage::FluButtonPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("Button"));
    // m_subTitleLabel->setText("FluentUI::FluCheckButton");
    m_infoLabel->setText(tr("This Page display Button examples."));

    auto displayBox1 = new FluDisplayBoxEx;
    //  displayBox1->setFixedHeight(140);
    displayBox1->setTitle(tr("A simple button with text content."));
    displayBox1->getCodeExpander()->setCodeByPath("../code/ButtonPageCode1.md");
    auto btn1 = new FluPushButton(this);
    btn1->setText(tr("Standard XAML button"));
    displayBox1->setBodyWidgetFixedHeight(96);
    displayBox1->getBodyContentLayout()->addWidget(btn1);

    auto checkBox = new FluCheckBox(tr("Disable Button"));
    //   displayBox1->getBodyRightLayout()->setAlignment(Qt::AlignTop);
    displayBox1->getBodyRightLayout()->addWidget(checkBox);

    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    auto displayBox2 = new FluDisplayBox;
    displayBox2->setTitle(tr("A Button with grapical content."));
    displayBox2->getCodeExpander()->setCodeByPath("../code/ButtonPageCode2.md");
    auto btn2 = new FluGraphicalButton;
    btn2->setIcon(QPixmap("../res/Slices.png"));
    displayBox2->setBodyWidgetFixedHeight(96);
    displayBox2->getBodyLayout()->addWidget(btn2);
    m_vScrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);
    // m_mainLayout->addStretch();

    auto displayBox3 = new FluDisplayBox;
    displayBox3->setTitle(tr("Accent style applied to Button."));
    displayBox3->getCodeExpander()->setCodeByPath("../code/ButtonPageCode3.md");
    auto btn3 = new FluStyleButton;
    btn3->setText(tr("Accent style button."));
    displayBox3->setBodyWidgetFixedHeight(96);
    displayBox3->getBodyLayout()->addWidget(btn3);
    m_vScrollView->getMainLayout()->addWidget(displayBox3, 0, Qt::AlignTop);

    onThemeChanged();
}

void FluButtonPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluButtonPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluButtonPage.qss", this);
    }
}
