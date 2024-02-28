#pragma once

#include <QFrame>

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluGraphicalButton.h"
#include "../FluControls/FluStyleButton.h"

class FluButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluButtonPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("Button");
        //m_subTitleLabel->setText("CppQtFluentUi888::FluCheckButton");
        m_infoLabel->setText("This Page display Button examples.");
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluButtonPage.qss", this);

        auto displayBox1 = new FluDisplayBox;
        //  displayBox1->setFixedHeight(140);
        displayBox1->setTitle("A simple button with text content.");
        displayBox1->getCodeExpander()->setCodeByPath("../code/ButtonPageCode1");
        auto btn1 = new FluPushButton(this);
        btn1->setText("Standard XAML button");
        displayBox1->setBodyWidgetFixedHeight(96);
        displayBox1->getBodyLayout()->addWidget(btn1);
        m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

        auto displayBox2 = new FluDisplayBox;
        displayBox2->setTitle("A Button with grapical content.");
        displayBox2->getCodeExpander()->setCodeByPath("../code/ButtonPageCode2");
        auto btn2 = new FluGraphicalButton;
        btn2->setIcon(QPixmap("../res/Slices.png"));
        displayBox2->setBodyWidgetFixedHeight(96);
        displayBox2->getBodyLayout()->addWidget(btn2);
        m_vScrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);
        // m_mainLayout->addStretch();

        auto displayBox3 = new FluDisplayBox;
        displayBox3->setTitle("Accent style applied to Button.");
        displayBox3->getCodeExpander()->setCodeByPath("../code/ButtonPageCode3");
        auto btn3 = new FluStyleButton;
        btn3->setText("Accent style button.");
        displayBox3->setBodyWidgetFixedHeight(96);
        displayBox3->getBodyLayout()->addWidget(btn3);
        m_vScrollView->getMainLayout()->addWidget(displayBox3, 0, Qt::AlignTop);

        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluButtonPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluButtonPage.qss", this);
        }
    }
};
