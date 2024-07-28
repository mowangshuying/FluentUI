#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluPasswordBox.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluPasswordBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluPasswordBoxPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("PasswordBox");
        m_infoLabel->setText(
            "A user can enter a single line of non-wrapping text in a PasswordBox control. The text is Masked by characters that you can specify by using the PasswordChar property, and you can specify the maximum number of characters that the user "
            "can enter by setting the MaxLength property.");

        auto displayBox1 = new FluDisplayBox;
        displayBox1->setTitle("A simple PasswordBox.");
        displayBox1->getCodeExpander()->setCodeByPath("../code/PasswordBoxPageCode1.md");

        auto passwordBox1 = new FluPasswordBox(this);
        passwordBox1->setFixedWidth(240);
        displayBox1->setBodyWidgetFixedHeight(96);
        displayBox1->getBodyLayout()->addWidget(passwordBox1);
        m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

        // maskC
        auto displayBox2 = new FluDisplayBox;
        displayBox2->setTitle("A PasswordBox with header, placeholder text and custom character.");
        displayBox2->getCodeExpander()->setCodeByPath("../code/PasswordBoxPageCode2.md");

        auto passwordBox2 = new FluPasswordBox(this);
        passwordBox2->setMaskC(0x2a);
        passwordBox2->setFixedWidth(240);
        displayBox2->setBodyWidgetFixedHeight(96);
        displayBox2->getBodyLayout()->addWidget(passwordBox2);
        m_vScrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPasswordBoxPage.qss", this);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPasswordBoxPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluPasswordBoxPage.qss", this);
        }
    }
};
